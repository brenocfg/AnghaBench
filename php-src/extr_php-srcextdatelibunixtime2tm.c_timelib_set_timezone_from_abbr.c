#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int have_zone; int /*<<< orphan*/ * tz_info; int /*<<< orphan*/  dst; int /*<<< orphan*/  zone_type; int /*<<< orphan*/  z; scalar_t__ tz_abbr; } ;
typedef  TYPE_1__ timelib_time ;
struct TYPE_6__ {int /*<<< orphan*/  dst; int /*<<< orphan*/  utc_offset; int /*<<< orphan*/  abbr; } ;
typedef  TYPE_2__ timelib_abbr_info ;

/* Variables and functions */
 int /*<<< orphan*/  TIMELIB_ZONETYPE_ABBR ; 
 int /*<<< orphan*/  timelib_free (scalar_t__) ; 
 scalar_t__ timelib_strdup (int /*<<< orphan*/ ) ; 

void timelib_set_timezone_from_abbr(timelib_time *t, timelib_abbr_info abbr_info)
{
	if (t->tz_abbr) {
		timelib_free(t->tz_abbr);
	}
	t->tz_abbr = timelib_strdup(abbr_info.abbr);

	t->z = abbr_info.utc_offset;
	t->have_zone = 1;
	t->zone_type = TIMELIB_ZONETYPE_ABBR;
	t->dst = abbr_info.dst;
	t->tz_info = NULL;
}