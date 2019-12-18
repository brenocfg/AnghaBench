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
 int /*<<< orphan*/  MODEM_SLEEP_T ; 
 scalar_t__ NULL_MODE ; 
 scalar_t__ PYEXEC_MODE_RAW_REPL ; 
 int /*<<< orphan*/  mp_hal_stdout_tx_str (char*) ; 
 int /*<<< orphan*/  mp_reset () ; 
 int /*<<< orphan*/  pyexec_event_repl_init () ; 
 scalar_t__ pyexec_friendly_repl () ; 
 scalar_t__ pyexec_mode_kind ; 
 scalar_t__ pyexec_raw_repl () ; 
 int /*<<< orphan*/  soft_reset () ; 
 int /*<<< orphan*/  uart_task_init () ; 
 int /*<<< orphan*/  wifi_fpm_do_sleep (int) ; 
 int /*<<< orphan*/  wifi_fpm_open () ; 
 int /*<<< orphan*/  wifi_fpm_set_sleep_type (int /*<<< orphan*/ ) ; 
 scalar_t__ wifi_get_opmode () ; 

void init_done(void) {
    // Configure sleep, and put the radio to sleep if no interfaces are active
    wifi_fpm_set_sleep_type(MODEM_SLEEP_T);
    if (wifi_get_opmode() == NULL_MODE) {
        wifi_fpm_open();
        wifi_fpm_do_sleep(0xfffffff);
    }

    #if MICROPY_REPL_EVENT_DRIVEN
    uart_task_init();
    #endif
    mp_reset();
    mp_hal_stdout_tx_str("\r\n");
    #if MICROPY_REPL_EVENT_DRIVEN
    pyexec_event_repl_init();
    #endif

    #if !MICROPY_REPL_EVENT_DRIVEN
soft_reset:
    for (;;) {
        if (pyexec_mode_kind == PYEXEC_MODE_RAW_REPL) {
            if (pyexec_raw_repl() != 0) {
                break;
            }
        } else {
            if (pyexec_friendly_repl() != 0) {
                break;
            }
        }
    }
    soft_reset();
    goto soft_reset;
    #endif
}