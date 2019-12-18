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
 int /*<<< orphan*/  IS31FL3731_write_register (size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** g_led_control_registers ; 
 scalar_t__ g_led_control_registers_update_required ; 

void IS31FL3731_update_led_control_registers(uint8_t addr, uint8_t index) {
    if (g_led_control_registers_update_required) {
        for (int i = 0; i < 18; i++) {
            IS31FL3731_write_register(addr, i, g_led_control_registers[index][i]);
        }
    }
}