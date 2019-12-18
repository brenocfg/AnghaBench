#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  timelib_tzinfo ;
typedef  int /*<<< orphan*/  timelib_tzdb ;

/* Variables and functions */
 int TIMELIB_ERROR_CORRUPT_NO_64BIT_PREAMBLE ; 
 int TIMELIB_ERROR_NO_SUCH_TIMEZONE ; 
 int TIMELIB_ERROR_UNSUPPORTED_VERSION ; 
 unsigned int TIMELIB_TZINFO_PHP ; 
 int /*<<< orphan*/  read_32bit_header (unsigned char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_64bit_header (unsigned char const**,int /*<<< orphan*/ *) ; 
 int read_64bit_transitions (unsigned char const**,int /*<<< orphan*/ *) ; 
 int read_64bit_types (unsigned char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_location (unsigned char const**,int /*<<< orphan*/ *) ; 
 int read_preamble (unsigned char const**,int /*<<< orphan*/ *,unsigned int*) ; 
 scalar_t__ seek_to_tz_position (unsigned char const**,char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  set_default_location_and_comments (unsigned char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_32bit_transitions (unsigned char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_32bit_types (unsigned char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_64bit_preamble (unsigned char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_posix_string (unsigned char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * timelib_tzinfo_ctor (char*) ; 
 int /*<<< orphan*/  timelib_tzinfo_dtor (int /*<<< orphan*/ *) ; 

timelib_tzinfo *timelib_parse_tzfile(char *timezone, const timelib_tzdb *tzdb, int *error_code)
{
	const unsigned char *tzf;
	timelib_tzinfo *tmp;
	int version;
	int transitions_result, types_result;
	unsigned int type; /* TIMELIB_TZINFO_PHP or TIMELIB_TZINFO_ZONEINFO */

	if (seek_to_tz_position(&tzf, timezone, tzdb)) {
		tmp = timelib_tzinfo_ctor(timezone);

		version = read_preamble(&tzf, tmp, &type);
		if (version < 2 || version > 3) {
			*error_code = TIMELIB_ERROR_UNSUPPORTED_VERSION;
			timelib_tzinfo_dtor(tmp);
			return NULL;
		}
//printf("- timezone: %s, version: %0d\n", timezone, version);

		read_32bit_header(&tzf, tmp);
		skip_32bit_transitions(&tzf, tmp);
		skip_32bit_types(&tzf, tmp);

		if (!skip_64bit_preamble(&tzf, tmp)) {
			/* 64 bit preamble is not in place */
			*error_code = TIMELIB_ERROR_CORRUPT_NO_64BIT_PREAMBLE;
			timelib_tzinfo_dtor(tmp);
			return NULL;
		}
		read_64bit_header(&tzf, tmp);
		if ((transitions_result = read_64bit_transitions(&tzf, tmp)) != 0) {
			/* Corrupt file as transitions do not increase */
			*error_code = transitions_result;
			timelib_tzinfo_dtor(tmp);
			return NULL;
		}
		if ((types_result = read_64bit_types(&tzf, tmp)) != 0) {
			*error_code = types_result;
			timelib_tzinfo_dtor(tmp);
			return NULL;
		}
		skip_posix_string(&tzf, tmp);

		if (type == TIMELIB_TZINFO_PHP) {
			read_location(&tzf, tmp);
		} else {
			set_default_location_and_comments(&tzf, tmp);
		}
	} else {
		*error_code = TIMELIB_ERROR_NO_SUCH_TIMEZONE;
		tmp = NULL;
	}

	return tmp;
}