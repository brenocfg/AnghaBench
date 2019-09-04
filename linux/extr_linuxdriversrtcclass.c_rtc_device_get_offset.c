#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int time64_t ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct rtc_device {scalar_t__ range_min; scalar_t__ range_max; int start_secs; int set_start_time; int offset_secs; TYPE_1__ dev; } ;

/* Variables and functions */
 int device_property_read_u32 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int mktime64 (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtc_device_get_offset(struct rtc_device *rtc)
{
	time64_t range_secs;
	u32 start_year;
	int ret;

	/*
	 * If RTC driver did not implement the range of RTC hardware device,
	 * then we can not expand the RTC range by adding or subtracting one
	 * offset.
	 */
	if (rtc->range_min == rtc->range_max)
		return;

	ret = device_property_read_u32(rtc->dev.parent, "start-year",
				       &start_year);
	if (!ret) {
		rtc->start_secs = mktime64(start_year, 1, 1, 0, 0, 0);
		rtc->set_start_time = true;
	}

	/*
	 * If user did not implement the start time for RTC driver, then no
	 * need to expand the RTC range.
	 */
	if (!rtc->set_start_time)
		return;

	range_secs = rtc->range_max - rtc->range_min + 1;

	/*
	 * If the start_secs is larger than the maximum seconds (rtc->range_max)
	 * supported by RTC hardware or the maximum seconds of new expanded
	 * range (start_secs + rtc->range_max - rtc->range_min) is less than
	 * rtc->range_min, which means the minimum seconds (rtc->range_min) of
	 * RTC hardware will be mapped to start_secs by adding one offset, so
	 * the offset seconds calculation formula should be:
	 * rtc->offset_secs = rtc->start_secs - rtc->range_min;
	 *
	 * If the start_secs is larger than the minimum seconds (rtc->range_min)
	 * supported by RTC hardware, then there is one region is overlapped
	 * between the original RTC hardware range and the new expanded range,
	 * and this overlapped region do not need to be mapped into the new
	 * expanded range due to it is valid for RTC device. So the minimum
	 * seconds of RTC hardware (rtc->range_min) should be mapped to
	 * rtc->range_max + 1, then the offset seconds formula should be:
	 * rtc->offset_secs = rtc->range_max - rtc->range_min + 1;
	 *
	 * If the start_secs is less than the minimum seconds (rtc->range_min),
	 * which is similar to case 2. So the start_secs should be mapped to
	 * start_secs + rtc->range_max - rtc->range_min + 1, then the
	 * offset seconds formula should be:
	 * rtc->offset_secs = -(rtc->range_max - rtc->range_min + 1);
	 *
	 * Otherwise the offset seconds should be 0.
	 */
	if (rtc->start_secs > rtc->range_max ||
	    rtc->start_secs + range_secs - 1 < rtc->range_min)
		rtc->offset_secs = rtc->start_secs - rtc->range_min;
	else if (rtc->start_secs > rtc->range_min)
		rtc->offset_secs = range_secs;
	else if (rtc->start_secs < rtc->range_min)
		rtc->offset_secs = -range_secs;
	else
		rtc->offset_secs = 0;
}