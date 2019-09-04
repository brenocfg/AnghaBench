#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  timelib_tzinfo ;
struct TYPE_6__ {int /*<<< orphan*/  abbr; int /*<<< orphan*/  is_dst; int /*<<< orphan*/  offset; } ;
typedef  TYPE_1__ timelib_time_offset ;
struct TYPE_7__ {int have_zone; int /*<<< orphan*/  zone_type; int /*<<< orphan*/  tz_abbr; int /*<<< orphan*/ * tz_info; int /*<<< orphan*/  dst; int /*<<< orphan*/  z; int /*<<< orphan*/  sse; } ;
typedef  TYPE_2__ timelib_time ;

/* Variables and functions */
 int /*<<< orphan*/  TIMELIB_ZONETYPE_ID ; 
 int /*<<< orphan*/  timelib_free (int /*<<< orphan*/ ) ; 
 TYPE_1__* timelib_get_time_zone_info (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timelib_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timelib_time_offset_dtor (TYPE_1__*) ; 

void timelib_set_timezone(timelib_time *t, timelib_tzinfo *tz)
{
	timelib_time_offset *gmt_offset;

	gmt_offset = timelib_get_time_zone_info(t->sse, tz);
	t->z = gmt_offset->offset;
/*
	if (t->dst != gmt_offset->is_dst) {
		printf("ERROR (%d, %d)\n", t->dst, gmt_offset->is_dst);
		exit(1);
	}
*/
	t->dst = gmt_offset->is_dst;
	t->tz_info = tz;
	if (t->tz_abbr) {
		timelib_free(t->tz_abbr);
	}
	t->tz_abbr = timelib_strdup(gmt_offset->abbr);
	timelib_time_offset_dtor(gmt_offset);

	t->have_zone = 1;
	t->zone_type = TIMELIB_ZONETYPE_ID;
}