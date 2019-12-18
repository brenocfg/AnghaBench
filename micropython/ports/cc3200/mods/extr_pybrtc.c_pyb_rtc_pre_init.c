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

/* Variables and functions */
 int /*<<< orphan*/  MAP_PRCMRTCInUseSet () ; 
 scalar_t__ MAP_PRCMSysResetCauseGet () ; 
 scalar_t__ PRCM_POWER_ON ; 
 int /*<<< orphan*/  pyb_rtc_reset () ; 

__attribute__ ((section (".boot")))
void pyb_rtc_pre_init(void) {
    // only if comming out of a power-on reset
    if (MAP_PRCMSysResetCauseGet() == PRCM_POWER_ON) {
        // Mark the RTC in use first
        MAP_PRCMRTCInUseSet();
        // reset the time and date
        pyb_rtc_reset();
    }
}