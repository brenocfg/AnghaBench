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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAP_PRCMRTCGet (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RTC_CYCLES_U16MS (int /*<<< orphan*/ ) ; 

void pyb_rtc_get_time (uint32_t *secs, uint16_t *msecs) {
    uint16_t cycles;
    MAP_PRCMRTCGet (secs, &cycles);
    *msecs = RTC_CYCLES_U16MS(cycles);
}