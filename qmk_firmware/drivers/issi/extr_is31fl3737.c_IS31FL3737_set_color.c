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
struct TYPE_3__ {size_t driver; size_t r; size_t g; size_t b; } ;
typedef  TYPE_1__ is31_led ;

/* Variables and functions */
 int DRIVER_LED_TOTAL ; 
 TYPE_1__* g_is31_leds ; 
 int /*<<< orphan*/ ** g_pwm_buffer ; 
 int g_pwm_buffer_update_required ; 

void IS31FL3737_set_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
    if (index >= 0 && index < DRIVER_LED_TOTAL) {
        is31_led led = g_is31_leds[index];

        g_pwm_buffer[led.driver][led.r] = red;
        g_pwm_buffer[led.driver][led.g] = green;
        g_pwm_buffer[led.driver][led.b] = blue;
        g_pwm_buffer_update_required    = true;
    }
}