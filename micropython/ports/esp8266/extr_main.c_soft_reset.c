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
 int /*<<< orphan*/  gc_sweep_all () ; 
 int /*<<< orphan*/  mp_hal_delay_us (int) ; 
 int /*<<< orphan*/  mp_hal_stdout_tx_str (char*) ; 
 int /*<<< orphan*/  mp_reset () ; 
 int /*<<< orphan*/  pyexec_event_repl_init () ; 

void soft_reset(void) {
    gc_sweep_all();
    mp_hal_stdout_tx_str("MPY: soft reboot\r\n");
    mp_hal_delay_us(10000); // allow UART to flush output
    mp_reset();
    #if MICROPY_REPL_EVENT_DRIVEN
    pyexec_event_repl_init();
    #endif
}