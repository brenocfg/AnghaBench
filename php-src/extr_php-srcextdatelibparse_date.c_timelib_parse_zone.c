#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  timelib_tzinfo ;
typedef  int /*<<< orphan*/  timelib_tzdb ;
typedef  int /*<<< orphan*/ * (* timelib_tz_get_wrapper ) (char*,int /*<<< orphan*/  const*,int*) ;
struct TYPE_4__ {int is_localtime; void* zone_type; int /*<<< orphan*/ * tz_info; scalar_t__ dst; } ;
typedef  TYPE_1__ timelib_time ;
typedef  int timelib_long ;

/* Variables and functions */
 void* TIMELIB_ZONETYPE_ABBR ; 
 void* TIMELIB_ZONETYPE_ID ; 
 void* TIMELIB_ZONETYPE_OFFSET ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  timelib_free (char*) ; 
 int timelib_lookup_abbr (char**,int*,char**,int*) ; 
 int timelib_parse_tz_cor (char**) ; 
 int /*<<< orphan*/  timelib_time_tz_abbr_update (TYPE_1__*,char*) ; 

timelib_long timelib_parse_zone(char **ptr, int *dst, timelib_time *t, int *tz_not_found, const timelib_tzdb *tzdb, timelib_tz_get_wrapper tz_wrapper)
{
	timelib_tzinfo *res;
	timelib_long            retval = 0;

	*tz_not_found = 0;

	while (**ptr == ' ' || **ptr == '\t' || **ptr == '(') {
		++*ptr;
	}
	if ((*ptr)[0] == 'G' && (*ptr)[1] == 'M' && (*ptr)[2] == 'T' && ((*ptr)[3] == '+' || (*ptr)[3] == '-')) {
		*ptr += 3;
	}
	if (**ptr == '+') {
		++*ptr;
		t->is_localtime = 1;
		t->zone_type = TIMELIB_ZONETYPE_OFFSET;
		*tz_not_found = 0;
		t->dst = 0;

		retval = timelib_parse_tz_cor(ptr);
	} else if (**ptr == '-') {
		++*ptr;
		t->is_localtime = 1;
		t->zone_type = TIMELIB_ZONETYPE_OFFSET;
		*tz_not_found = 0;
		t->dst = 0;

		retval = -1 * timelib_parse_tz_cor(ptr);
	} else {
		int found = 0;
		timelib_long offset = 0;
		char *tz_abbr;

		t->is_localtime = 1;

		/* First, we lookup by abbreviation only */
		offset = timelib_lookup_abbr(ptr, dst, &tz_abbr, &found);
		if (found) {
			t->zone_type = TIMELIB_ZONETYPE_ABBR;
			timelib_time_tz_abbr_update(t, tz_abbr);
		}

		/* Otherwise, we look if we have a TimeZone identifier */
		if (!found || strcmp("UTC", tz_abbr) == 0) {
			int dummy_error_code;

			if ((res = tz_wrapper(tz_abbr, tzdb, &dummy_error_code)) != NULL) {
				t->tz_info = res;
				t->zone_type = TIMELIB_ZONETYPE_ID;
				found++;
			}
		}
		timelib_free(tz_abbr);
		*tz_not_found = (found == 0);
		retval = offset;
	}
	while (**ptr == ')') {
		++*ptr;
	}
	return retval;
}