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
 int LED0 ; 
 int /*<<< orphan*/  MICROPY_HW_LED_OFF (int) ; 
 int /*<<< orphan*/  MICROPY_HW_LED_ON (int) ; 

void led_state(int led, int val) {
    if (led == 1) {
        led = LED0;
    }
    if (val) {
        MICROPY_HW_LED_ON(led);
    } else {
        MICROPY_HW_LED_OFF(led);
    }
}