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
typedef  scalar_t__ battery_led_t ;

/* Variables and functions */
 int DDRF ; 
 scalar_t__ LED_OFF ; 
 scalar_t__ LED_ON ; 
 scalar_t__ LED_TOGGLE ; 
 int PINF ; 
 int PORTF ; 

void battery_led(battery_led_t val)
{
    if (val == LED_TOGGLE) {
        // Toggle LED
        DDRF  |=  (1<<5);
        PINF  |=  (1<<5);
    } else if (val == LED_ON) {
        // On overriding charger status
        DDRF  |=  (1<<5);
        PORTF &= ~(1<<5);
    } else if (val == LED_OFF) {
        // Off overriding charger status
        DDRF  |=  (1<<5);
        PORTF |=  (1<<5);
    } else {
        // Display charger status
        DDRF  &= ~(1<<5);
        PORTF &= ~(1<<5);
    }
}