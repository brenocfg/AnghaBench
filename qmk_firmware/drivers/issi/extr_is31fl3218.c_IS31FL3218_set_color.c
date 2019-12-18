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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/ * g_pwm_buffer ; 
 int g_pwm_buffer_update_required ; 

void IS31FL3218_set_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
    g_pwm_buffer[index * 3 + 0]  = red;
    g_pwm_buffer[index * 3 + 1]  = green;
    g_pwm_buffer[index * 3 + 2]  = blue;
    g_pwm_buffer_update_required = true;
}