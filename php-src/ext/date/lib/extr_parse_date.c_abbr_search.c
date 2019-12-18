#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char const* name; int gmtoffset; int type; } ;
typedef  TYPE_1__ timelib_tz_lookup_table ;
typedef  int timelib_long ;

/* Variables and functions */
 scalar_t__ timelib_strcasecmp (char const*,char const*) ; 
 TYPE_1__* timelib_timezone_fallbackmap ; 
 TYPE_1__* timelib_timezone_lookup ; 
 TYPE_1__ const* timelib_timezone_utc ; 

__attribute__((used)) static const timelib_tz_lookup_table* abbr_search(const char *word, timelib_long gmtoffset, int isdst)
{
	int first_found = 0;
	const timelib_tz_lookup_table  *tp, *first_found_elem = NULL;
	const timelib_tz_lookup_table  *fmp;

	if (timelib_strcasecmp("utc", word) == 0 || timelib_strcasecmp("gmt", word) == 0) {
		return timelib_timezone_utc;
	}

	for (tp = timelib_timezone_lookup; tp->name; tp++) {
		if (timelib_strcasecmp(word, tp->name) == 0) {
			if (!first_found) {
				first_found = 1;
				first_found_elem = tp;
				if (gmtoffset == -1) {
					return tp;
				}
			}
			if (tp->gmtoffset == gmtoffset) {
				return tp;
			}
		}
	}
	if (first_found) {
		return first_found_elem;
	}

	/* Still didn't find anything, let's find the zone solely based on
	 * offset/isdst then */
	for (fmp = timelib_timezone_fallbackmap; fmp->name; fmp++) {
		if (fmp->gmtoffset == gmtoffset && fmp->type == isdst) {
			return fmp;
		}
	}
	return NULL;
}