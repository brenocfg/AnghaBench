#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * tz_abbr; } ;
typedef  TYPE_1__ timelib_time ;

/* Variables and functions */
 int /*<<< orphan*/  TIMELIB_TIME_FREE (int /*<<< orphan*/ *) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/ * timelib_strdup (char*) ; 
 int /*<<< orphan*/  toupper (char) ; 

void timelib_time_tz_abbr_update(timelib_time* tm, char* tz_abbr)
{
	unsigned int i;
	size_t tz_abbr_len = strlen(tz_abbr);

	TIMELIB_TIME_FREE(tm->tz_abbr);
	tm->tz_abbr = timelib_strdup(tz_abbr);
	for (i = 0; i < tz_abbr_len; i++) {
		tm->tz_abbr[i] = toupper(tz_abbr[i]);
	}
}