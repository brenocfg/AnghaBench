#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {size_t driver; int v; } ;
typedef  TYPE_1__ is31_led ;

/* Variables and functions */
 int LED_DRIVER_LED_COUNT ; 
 TYPE_1__* g_is31_leds ; 
 int /*<<< orphan*/ ** g_pwm_buffer ; 
 int g_pwm_buffer_update_required ; 

void IS31FL3731_set_value(int index, uint8_t value) {
    if (index >= 0 && index < LED_DRIVER_LED_COUNT) {
        is31_led led = g_is31_leds[index];

        // Subtract 0x24 to get the second index of g_pwm_buffer
        g_pwm_buffer[led.driver][led.v - 0x24] = value;
        g_pwm_buffer_update_required           = true;
    }
}