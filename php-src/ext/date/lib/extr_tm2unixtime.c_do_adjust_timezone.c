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
typedef  int /*<<< orphan*/  timelib_tzinfo ;
struct TYPE_7__ {int offset; int transition_time; int is_dst; int /*<<< orphan*/  abbr; } ;
typedef  TYPE_1__ timelib_time_offset ;
struct TYPE_8__ {int zone_type; int is_localtime; int z; int dst; int sse; int /*<<< orphan*/  tz_abbr; int /*<<< orphan*/ * tz_info; } ;
typedef  TYPE_2__ timelib_time ;
typedef  int timelib_sll ;

/* Variables and functions */
#define  TIMELIB_ZONETYPE_ABBR 130 
#define  TIMELIB_ZONETYPE_ID 129 
#define  TIMELIB_ZONETYPE_OFFSET 128 
 int /*<<< orphan*/  timelib_free (int /*<<< orphan*/ ) ; 
 TYPE_1__* timelib_get_time_zone_info (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timelib_set_timezone (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timelib_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timelib_time_offset_dtor (TYPE_1__*) ; 

__attribute__((used)) static timelib_sll do_adjust_timezone(timelib_time *tz, timelib_tzinfo *tzi)
{
	switch (tz->zone_type) {
		case TIMELIB_ZONETYPE_OFFSET:

			tz->is_localtime = 1;
			return -tz->z;
			break;

		case TIMELIB_ZONETYPE_ABBR: {
			timelib_sll tmp;

			tz->is_localtime = 1;
			tmp = -tz->z;
			tmp -= tz->dst * 3600;
			return tmp;
			}
			break;

		case TIMELIB_ZONETYPE_ID:
			tzi = tz->tz_info;
			/* Break intentionally missing */

		default:
			/* No timezone in struct, fallback to reference if possible */
			if (tzi) {
				timelib_time_offset *before, *after;
				timelib_sll          tmp;
				int                  in_transition;

				tz->is_localtime = 1;
				before = timelib_get_time_zone_info(tz->sse, tzi);
				after = timelib_get_time_zone_info(tz->sse - before->offset, tzi);
				timelib_set_timezone(tz, tzi);

				in_transition = (
					((tz->sse - after->offset) >= (after->transition_time + (before->offset - after->offset))) &&
					((tz->sse - after->offset) < after->transition_time)
				);

				if ((before->offset != after->offset) && !in_transition) {
					tmp = -after->offset;
				} else {
					tmp = -tz->z;
				}
				timelib_time_offset_dtor(before);
				timelib_time_offset_dtor(after);

				{
					timelib_time_offset *gmt_offset;

					gmt_offset = timelib_get_time_zone_info(tz->sse + tmp, tzi);
					tz->z = gmt_offset->offset;

					tz->dst = gmt_offset->is_dst;
					if (tz->tz_abbr) {
						timelib_free(tz->tz_abbr);
					}
					tz->tz_abbr = timelib_strdup(gmt_offset->abbr);
					timelib_time_offset_dtor(gmt_offset);
				}
				return tmp;
			}
	}
	return 0;
}