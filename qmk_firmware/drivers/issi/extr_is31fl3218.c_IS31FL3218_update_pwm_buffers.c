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
 int /*<<< orphan*/  IS31FL3218_write_pwm_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS31FL3218_write_register (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ISSI_REG_UPDATE ; 
 int /*<<< orphan*/  g_pwm_buffer ; 
 int g_pwm_buffer_update_required ; 

void IS31FL3218_update_pwm_buffers(void) {
    if (g_pwm_buffer_update_required) {
        IS31FL3218_write_pwm_buffer(g_pwm_buffer);
        // Load PWM registers and LED Control register data
        IS31FL3218_write_register(ISSI_REG_UPDATE, 0x01);
    }
    g_pwm_buffer_update_required = false;
}