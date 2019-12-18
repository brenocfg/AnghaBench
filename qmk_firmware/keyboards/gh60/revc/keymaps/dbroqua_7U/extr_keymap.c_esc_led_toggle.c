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
 int esc_led ; 
 int /*<<< orphan*/  gh60_esc_led_off () ; 
 int /*<<< orphan*/  gh60_esc_led_on () ; 

void esc_led_toggle(void) {
    if (esc_led == 0){
        esc_led = 1;
        gh60_esc_led_on();
    } else {
        esc_led = 0;
        gh60_esc_led_off();
    }
}