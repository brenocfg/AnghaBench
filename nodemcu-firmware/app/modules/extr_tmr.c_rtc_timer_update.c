#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int last_rtc_time ; 
 scalar_t__ last_rtc_time_us ; 
 int rtc2usec (int) ; 
 scalar_t__ rtc_time_cali ; 
 int system_get_rtc_time () ; 
 scalar_t__ system_rtc_clock_cali_proc () ; 

__attribute__((used)) inline static uint64_t rtc_timer_update(bool do_calibration){
	if (do_calibration || rtc_time_cali==0)
		rtc_time_cali=system_rtc_clock_cali_proc();

	uint32_t current = system_get_rtc_time();
	uint32_t since_last=current-last_rtc_time; // This will transparently deal with wraparound
	uint32_t us_since_last=rtc2usec(since_last);
	uint64_t now=last_rtc_time_us+us_since_last;

	// Only update if at least 100ms has passed since we last updated.
	// This prevents the rounding errors in rtc2usec from accumulating
	if (us_since_last>=100000)
	{
		last_rtc_time=current;
		last_rtc_time_us=now;
	}
	return now;
}