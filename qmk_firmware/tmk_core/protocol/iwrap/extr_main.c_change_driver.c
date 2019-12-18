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
typedef  int /*<<< orphan*/  host_driver_t ;

/* Variables and functions */
 int /*<<< orphan*/  _delay_ms (int) ; 
 int /*<<< orphan*/  clear_keyboard () ; 
 int /*<<< orphan*/  host_set_driver (int /*<<< orphan*/ *) ; 

void change_driver(host_driver_t *driver) {
    /*
    host_clear_keyboard_report();
    host_swap_keyboard_report();
    host_clear_keyboard_report();
    host_send_keyboard_report();
    */
    clear_keyboard();
    _delay_ms(1000);
    host_set_driver(driver);
}