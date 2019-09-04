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
struct TYPE_6__ {int /*<<< orphan*/  offset; } ;
typedef  TYPE_1__ timelib_time_offset ;
struct TYPE_7__ {int zone_type; int dst; int /*<<< orphan*/  tz_info; int /*<<< orphan*/  sse; int /*<<< orphan*/  z; } ;
typedef  TYPE_2__ timelib_time ;
typedef  int /*<<< orphan*/  timelib_sll ;

/* Variables and functions */
#define  TIMELIB_ZONETYPE_ABBR 130 
#define  TIMELIB_ZONETYPE_ID 129 
#define  TIMELIB_ZONETYPE_OFFSET 128 
 TYPE_1__* timelib_get_time_zone_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timelib_time_offset_dtor (TYPE_1__*) ; 

timelib_sll timelib_get_current_offset(timelib_time *t)
{
	timelib_time_offset *gmt_offset;
	timelib_sll retval;

	switch (t->zone_type) {
		case TIMELIB_ZONETYPE_ABBR:
		case TIMELIB_ZONETYPE_OFFSET:
			return t->z + (t->dst * 3600);

		case TIMELIB_ZONETYPE_ID:
			gmt_offset = timelib_get_time_zone_info(t->sse, t->tz_info);
			retval = gmt_offset->offset;
			timelib_time_offset_dtor(gmt_offset);
			return retval;

		default:
			return 0;
	}
}