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
struct TYPE_3__ {size_t driver; int r; int g; int b; } ;
typedef  TYPE_1__ is31_led ;

/* Variables and functions */
 int DRIVER_LED_TOTAL ; 
 TYPE_1__* g_is31_leds ; 
 int /*<<< orphan*/ ** g_pwm_buffer ; 
 int* g_pwm_buffer_update_required ; 

void IS31FL3731_set_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
    if (index >= 0 && index < DRIVER_LED_TOTAL) {
        is31_led led = g_is31_leds[index];

        // Subtract 0x24 to get the second index of g_pwm_buffer
        g_pwm_buffer[led.driver][led.r - 0x24]   = red;
        g_pwm_buffer[led.driver][led.g - 0x24]   = green;
        g_pwm_buffer[led.driver][led.b - 0x24]   = blue;
        g_pwm_buffer_update_required[led.driver] = true;
    }
}