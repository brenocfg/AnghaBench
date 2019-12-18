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
 int /*<<< orphan*/  IS31FL3218_write_register (scalar_t__,int) ; 
 scalar_t__ ISSI_REG_CONTROL ; 
 scalar_t__ ISSI_REG_PWM ; 
 scalar_t__ ISSI_REG_RESET ; 
 scalar_t__ ISSI_REG_SHUTDOWN ; 
 scalar_t__ ISSI_REG_UPDATE ; 

void IS31FL3218_init(void) {
    // In case we ever want to reinitialize (?)
    IS31FL3218_write_register(ISSI_REG_RESET, 0x00);

    // Turn off software shutdown
    IS31FL3218_write_register(ISSI_REG_SHUTDOWN, 0x01);

    // Set all PWM values to zero
    for (uint8_t i = 0; i < 18; i++) {
        IS31FL3218_write_register(ISSI_REG_PWM + i, 0x00);
    }

    // Enable all channels
    for (uint8_t i = 0; i < 3; i++) {
        IS31FL3218_write_register(ISSI_REG_CONTROL + i, 0b00111111);
    }

    // Load PWM registers and LED Control register data
    IS31FL3218_write_register(ISSI_REG_UPDATE, 0x01);
}