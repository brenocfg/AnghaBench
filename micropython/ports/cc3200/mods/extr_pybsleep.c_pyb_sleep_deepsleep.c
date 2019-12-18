#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* rtc_obj; } ;
struct TYPE_3__ {int pwrmode; scalar_t__ irq_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAILED_SLEEP_DELAY_MS ; 
 int /*<<< orphan*/  MAP_PRCMHibernateEnter () ; 
 int /*<<< orphan*/  MAP_PRCMLPDSWakeupSourceDisable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRCM_HIB_SLOW_CLK_CTR ; 
 int PYB_PWR_MODE_HIBERNATE ; 
 int /*<<< orphan*/  SL_STOP_TIMEOUT ; 
 int /*<<< orphan*/  mp_hal_delay_ms (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pyb_sleep_flash_powerdown () ; 
 int /*<<< orphan*/  pyb_sleep_iopark (int) ; 
 TYPE_2__ pybsleep_data ; 
 int /*<<< orphan*/  setup_timer_hibernate_wake () ; 
 int /*<<< orphan*/  wlan_stop (int /*<<< orphan*/ ) ; 

void pyb_sleep_deepsleep (void) {
    // check if we should enable timer wake-up
    if (pybsleep_data.rtc_obj->irq_enabled && (pybsleep_data.rtc_obj->pwrmode & PYB_PWR_MODE_HIBERNATE)) {
        if (!setup_timer_hibernate_wake()) {
            // hibernating is not possible, wait for the forced interrupt and return
            mp_hal_delay_ms(FAILED_SLEEP_DELAY_MS);
            return;
        }
    } else {
        // disable the timer as hibernate wake source
        MAP_PRCMLPDSWakeupSourceDisable(PRCM_HIB_SLOW_CLK_CTR);
    }

    wlan_stop(SL_STOP_TIMEOUT);
    pyb_sleep_flash_powerdown();
    // must be done just before entering hibernate mode
    pyb_sleep_iopark(true);
    MAP_PRCMHibernateEnter();
}