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
 int /*<<< orphan*/  _delay_ms (int) ; 
 int /*<<< orphan*/  iwrap_check_connection () ; 
 int /*<<< orphan*/  iwrap_mux_send (char*) ; 
 int /*<<< orphan*/  iwrap_send (char*) ; 

void iwrap_init(void) {
    // reset iWRAP if in already MUX mode after AVR software-reset
    iwrap_send("RESET");
    iwrap_mux_send("RESET");
    _delay_ms(3000);
    iwrap_send("\r\nSET CONTROL MUX 1\r\n");
    _delay_ms(500);
    iwrap_check_connection();
}