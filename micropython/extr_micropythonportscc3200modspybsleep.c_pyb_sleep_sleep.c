#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint ;
typedef  int /*<<< orphan*/  nlr_buf_t ;
struct TYPE_6__ {TYPE_2__* wlan_obj; TYPE_1__* rtc_obj; } ;
struct TYPE_5__ {scalar_t__ irq_enabled; } ;
struct TYPE_4__ {int pwrmode; scalar_t__ irq_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAILED_SLEEP_DELAY_MS ; 
 int /*<<< orphan*/  MAP_PRCMLPDSWakeupSourceDisable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAP_PRCMLPDSWakeupSourceEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRCM_LPDS_HOST_IRQ ; 
 int /*<<< orphan*/  PRCM_LPDS_TIMER ; 
 int PYB_PWR_MODE_LPDS ; 
 int /*<<< orphan*/  disable_irq () ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_hal_delay_ms (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlr_pop () ; 
 scalar_t__ nlr_push (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pyb_sleep_suspend_enter () ; 
 TYPE_3__ pybsleep_data ; 
 int /*<<< orphan*/  server_sleep_sockets () ; 
 int /*<<< orphan*/  setup_timer_lpds_wake () ; 

void pyb_sleep_sleep (void) {
    nlr_buf_t nlr;

    // check if we should enable timer wake-up
    if (pybsleep_data.rtc_obj->irq_enabled && (pybsleep_data.rtc_obj->pwrmode & PYB_PWR_MODE_LPDS)) {
        if (!setup_timer_lpds_wake()) {
            // lpds entering is not possible, wait for the forced interrupt and return
            mp_hal_delay_ms(FAILED_SLEEP_DELAY_MS);
            return;
        }
    } else {
        // disable the timer as wake source
        MAP_PRCMLPDSWakeupSourceDisable(PRCM_LPDS_TIMER);
    }

    // do we need network wake-up?
    if (pybsleep_data.wlan_obj->irq_enabled) {
        MAP_PRCMLPDSWakeupSourceEnable (PRCM_LPDS_HOST_IRQ);
        server_sleep_sockets();
    } else {
        MAP_PRCMLPDSWakeupSourceDisable (PRCM_LPDS_HOST_IRQ);
    }

    // entering and exiting suspended mode must be an atomic operation
    // therefore interrupts need to be disabled
    uint primsk = disable_irq();
    if (nlr_push(&nlr) == 0) {
        pyb_sleep_suspend_enter();
        nlr_pop();
    }

    // an exception is always raised when exiting suspend mode
    enable_irq(primsk);
}