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
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  int int64_t ;
typedef  int /*<<< orphan*/  delta ;
typedef  int /*<<< orphan*/  cal ;

/* Variables and functions */
 int /*<<< orphan*/  MEM_CAL_ADDR ; 
 int /*<<< orphan*/  MEM_DELTA_ADDR ; 
 scalar_t__ rtc_last_ticks ; 
 scalar_t__ system_get_rtc_time () ; 
 int /*<<< orphan*/  system_rtc_mem_read (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  system_rtc_mem_write (int /*<<< orphan*/ ,int*,int) ; 

uint64_t pyb_rtc_get_us_since_2000() {
    uint32_t cal;
    int64_t delta;
    uint32_t rtc_ticks;

    system_rtc_mem_read(MEM_CAL_ADDR, &cal, sizeof(cal));
    system_rtc_mem_read(MEM_DELTA_ADDR, &delta, sizeof(delta));

    // ESP-SDK system_get_rtc_time() only returns uint32 and therefore
    // overflow about every 7:45h.  Thus, we have to check for
    // overflow and handle it.
    rtc_ticks = system_get_rtc_time();
    if (rtc_ticks < rtc_last_ticks) {
        // Adjust delta because of RTC overflow.
        delta += (uint64_t)cal << 20;
        system_rtc_mem_write(MEM_DELTA_ADDR, &delta, sizeof(delta));
    }
    rtc_last_ticks = rtc_ticks;

    return (((uint64_t)rtc_ticks * cal) >> 12) + delta;
}