#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int pyb_led_t ;
typedef  int /*<<< orphan*/  pin_obj_t ;
struct TYPE_2__ {int /*<<< orphan*/ * led_pin; } ;

/* Variables and functions */
 int /*<<< orphan*/  MICROPY_HW_LED_OFF (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  MICROPY_HW_LED_ON (int /*<<< orphan*/  const*) ; 
 int NUM_LEDS ; 
 TYPE_1__* pyb_led_obj ; 

void led_state(pyb_led_t led, int state) {
    if (led < 1 || led > NUM_LEDS) {
        return;
    }
    const pin_obj_t *led_pin = pyb_led_obj[led - 1].led_pin;
    //printf("led_state(%d,%d)\n", led, state);
    if (state == 0) {
        // turn LED off
        MICROPY_HW_LED_OFF(led_pin);
    } else {
        // turn LED on
        MICROPY_HW_LED_ON(led_pin);
    }
}