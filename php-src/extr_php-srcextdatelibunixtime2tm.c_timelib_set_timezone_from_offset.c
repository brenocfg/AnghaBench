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
struct TYPE_3__ {int have_zone; int /*<<< orphan*/ * tz_info; scalar_t__ dst; int /*<<< orphan*/  zone_type; int /*<<< orphan*/  z; int /*<<< orphan*/ * tz_abbr; } ;
typedef  TYPE_1__ timelib_time ;
typedef  int /*<<< orphan*/  timelib_sll ;

/* Variables and functions */
 int /*<<< orphan*/  TIMELIB_ZONETYPE_OFFSET ; 
 int /*<<< orphan*/  timelib_free (int /*<<< orphan*/ *) ; 

void timelib_set_timezone_from_offset(timelib_time *t, timelib_sll utc_offset)
{
	if (t->tz_abbr) {
		timelib_free(t->tz_abbr);
	}
	t->tz_abbr = NULL;

	t->z = utc_offset;
	t->have_zone = 1;
	t->zone_type = TIMELIB_ZONETYPE_OFFSET;
	t->dst = 0;
	t->tz_info = NULL;
}