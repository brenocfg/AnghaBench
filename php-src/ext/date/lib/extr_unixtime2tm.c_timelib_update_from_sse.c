#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ offset; } ;
typedef  TYPE_1__ timelib_time_offset ;
struct TYPE_8__ {int z; int dst; int zone_type; int is_localtime; int have_zone; scalar_t__ sse; int /*<<< orphan*/  tz_info; } ;
typedef  TYPE_2__ timelib_time ;
typedef  scalar_t__ timelib_sll ;

/* Variables and functions */
#define  TIMELIB_ZONETYPE_ABBR 130 
#define  TIMELIB_ZONETYPE_ID 129 
#define  TIMELIB_ZONETYPE_OFFSET 128 
 TYPE_1__* timelib_get_time_zone_info (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timelib_time_offset_dtor (TYPE_1__*) ; 
 int /*<<< orphan*/  timelib_unixtime2gmt (TYPE_2__*,scalar_t__) ; 

void timelib_update_from_sse(timelib_time *tm)
{
	timelib_sll sse;
	int z = tm->z;
	signed int dst = tm->dst;

	sse = tm->sse;

	switch (tm->zone_type) {
		case TIMELIB_ZONETYPE_ABBR:
		case TIMELIB_ZONETYPE_OFFSET: {
			timelib_unixtime2gmt(tm, tm->sse + tm->z + (tm->dst * 3600));

			goto cleanup;
		}

		case TIMELIB_ZONETYPE_ID: {
			timelib_time_offset *gmt_offset;

			gmt_offset = timelib_get_time_zone_info(tm->sse, tm->tz_info);
			timelib_unixtime2gmt(tm, tm->sse + gmt_offset->offset);
			timelib_time_offset_dtor(gmt_offset);

			goto cleanup;
		}

		default:
			timelib_unixtime2gmt(tm, tm->sse);
			goto cleanup;
	}
cleanup:
	tm->sse = sse;
	tm->is_localtime = 1;
	tm->have_zone = 1;
	tm->z = z;
	tm->dst = dst;
}