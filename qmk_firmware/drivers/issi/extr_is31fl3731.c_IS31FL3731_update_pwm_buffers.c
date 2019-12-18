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
typedef  size_t uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  IS31FL3731_write_pwm_buffer (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * g_pwm_buffer ; 
 int* g_pwm_buffer_update_required ; 

void IS31FL3731_update_pwm_buffers(uint8_t addr, uint8_t index) {
    if (g_pwm_buffer_update_required[index]) {
        IS31FL3731_write_pwm_buffer(addr, g_pwm_buffer[index]);
    }
    g_pwm_buffer_update_required[index] = false;
}