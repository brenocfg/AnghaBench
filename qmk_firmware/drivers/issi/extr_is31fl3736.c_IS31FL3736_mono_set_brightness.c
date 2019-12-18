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
 size_t** g_pwm_buffer ; 
 int g_pwm_buffer_update_required ; 

void IS31FL3736_mono_set_brightness(int index, uint8_t value) {
    if (index >= 0 && index < 96) {
        // Index in range 0..95 -> A1..A8, B1..B8, etc.
        // Map index 0..95 to registers 0x00..0xBE (interleaved)
        uint8_t pwm_register          = index * 2;
        g_pwm_buffer[0][pwm_register] = value;
        g_pwm_buffer_update_required  = true;
    }
}