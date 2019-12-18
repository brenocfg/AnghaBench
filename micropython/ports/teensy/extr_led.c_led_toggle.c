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
typedef  int pyb_led_t ;
struct TYPE_4__ {int pin_mask; TYPE_2__* gpio; } ;
typedef  TYPE_1__ pin_obj_t ;
struct TYPE_6__ {TYPE_1__* led_pin; } ;
struct TYPE_5__ {int PDOR; int PCOR; int PSOR; } ;
typedef  TYPE_2__ GPIO_TypeDef ;

/* Variables and functions */
 int NUM_LEDS ; 
 TYPE_3__* pyb_led_obj ; 

void led_toggle(pyb_led_t led) {
    if (led < 1 || led > NUM_LEDS) {
        return;
    }
    const pin_obj_t *led_pin = pyb_led_obj[led - 1].led_pin;
    GPIO_TypeDef *gpio = led_pin->gpio;

    // We don't know if we're turning the LED on or off, but we don't really
    // care. Just invert the state.
    if (gpio->PDOR & led_pin->pin_mask) {
        // pin is high, make it low
        gpio->PCOR = led_pin->pin_mask;
    } else {
        // pin is low, make it high
        gpio->PSOR = led_pin->pin_mask;
    }
}