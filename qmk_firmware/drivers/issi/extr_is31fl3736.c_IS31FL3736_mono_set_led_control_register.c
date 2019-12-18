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
typedef  int uint8_t ;

/* Variables and functions */
 int** g_led_control_registers ; 
 int g_led_control_registers_update_required ; 

void IS31FL3736_mono_set_led_control_register(uint8_t index, bool enabled) {
    // Index in range 0..95 -> A1..A8, B1..B8, etc.

    // Map index 0..95 to registers 0x00..0xBE (interleaved)
    uint8_t pwm_register = index * 2;
    // Map register 0x00..0xBE (interleaved) into control register and bit
    uint8_t control_register = pwm_register / 8;
    uint8_t bit              = pwm_register % 8;

    if (enabled) {
        g_led_control_registers[0][control_register] |= (1 << bit);
    } else {
        g_led_control_registers[0][control_register] &= ~(1 << bit);
    }

    g_led_control_registers_update_required = true;
}