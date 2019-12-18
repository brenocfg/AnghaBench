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
 int /*<<< orphan*/  dk60_blink_all_leds () ; 
 int /*<<< orphan*/  led_init_ports () ; 
 int /*<<< orphan*/  matrix_init_user () ; 

void matrix_init_kb(void) {
    led_init_ports();
    dk60_blink_all_leds();

    matrix_init_user();
}