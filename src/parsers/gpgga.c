#include "../nmea/parser_types.h"
#include "gpgga.h"
#include "parse.h"

init_f
init(nmea_sentence_parser_s *parser)
{
	/* Declare what sentence type to parse */
	parser->type = NMEA_GPGGA;

	return 0;
}

allocate_data_f
allocate_data()
{
	return malloc(sizeof(nmea_gpgga_s));
}

set_default_f
set_default(nmea_s *nmea_data)
{
	memset(nmea_data, 0, sizeof(nmea_gpgga_s));
}

free_data_f
free_data(nmea_s *nmea_data)
{
	free(nmea_data);
}

parse_f
parse(char *value, int val_index, nmea_s *nmea_data)
{
	nmea_gpgga_s *data = (nmea_gpgga_s *) nmea_data;

	switch (val_index) {
		case NMEA_GPGGA_TIME:
			/* Parse time */
			if (-1 == nmea_time_parse(value, &data->time)) {
				return (parse_f) -1;
			}
			break;

		case NMEA_GPGGA_LATITUDE:
			/* Parse latitude */
			if (-1 == nmea_position_parse(value, &data->latitude)) {
				return (parse_f) -1;
			}
			break;

		case NMEA_GPGGA_LATITUDE_CARDINAL:
			/* Parse cardinal direction */
			data->latitude.cardinal = nmea_cardinal_direction_parse(value);
			if (NMEA_CARDINAL_DIR_UNKNOWN == data->latitude.cardinal) {
				return (parse_f) -1;
			}
			break;

		case NMEA_GPGGA_LONGITUDE:
			/* Parse longitude */
			if (-1 == nmea_position_parse(value, &data->longitude)) {
				return (parse_f) -1;
			}
			break;

		case NMEA_GPGGA_LONGITUDE_CARDINAL:
			/* Parse cardinal direction */
			data->longitude.cardinal = nmea_cardinal_direction_parse(value);
			if (NMEA_CARDINAL_DIR_UNKNOWN == data->longitude.cardinal) {
				return (parse_f) -1;
			}
			break;

		case NMEA_GPGGA_N_SATELLITES:
			/* Parse number of satellies */
			data->n_satellites = atoi(value);
			break;

		case NMEA_GPGGA_ALTITUDE:
			/* Parse altitude */
			data->altitude = atoi(value);
			break;

		case NMEA_GPGGA_ALTITUDE_UNIT:
			/* Parse altitude unit */
			data->altitude_unit = *value;
			break;

		default:
			break;
	}

	return (parse_f) 0;
}