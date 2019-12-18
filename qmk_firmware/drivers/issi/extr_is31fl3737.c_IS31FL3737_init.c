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
 int /*<<< orphan*/  IS31FL3737_write_register (int /*<<< orphan*/ ,int,int) ; 
 int ISSI_COMMANDREGISTER ; 
 int ISSI_COMMANDREGISTER_WRITELOCK ; 
 int ISSI_PAGE_FUNCTION ; 
 int ISSI_PAGE_LEDCONTROL ; 
 int ISSI_PAGE_PWM ; 
 int ISSI_REG_CONFIGURATION ; 
 int ISSI_REG_GLOBALCURRENT ; 
 int /*<<< orphan*/  _delay_ms (int) ; 
 int /*<<< orphan*/  wait_ms (int) ; 

void IS31FL3737_init(uint8_t addr) {
    // In order to avoid the LEDs being driven with garbage data
    // in the LED driver's PWM registers, shutdown is enabled last.
    // Set up the mode and other settings, clear the PWM registers,
    // then disable software shutdown.

    // Unlock the command register.
    IS31FL3737_write_register(addr, ISSI_COMMANDREGISTER_WRITELOCK, 0xC5);

    // Select PG0
    IS31FL3737_write_register(addr, ISSI_COMMANDREGISTER, ISSI_PAGE_LEDCONTROL);
    // Turn off all LEDs.
    for (int i = 0x00; i <= 0x17; i++) {
        IS31FL3737_write_register(addr, i, 0x00);
    }

    // Unlock the command register.
    IS31FL3737_write_register(addr, ISSI_COMMANDREGISTER_WRITELOCK, 0xC5);

    // Select PG1
    IS31FL3737_write_register(addr, ISSI_COMMANDREGISTER, ISSI_PAGE_PWM);
    // Set PWM on all LEDs to 0
    // No need to setup Breath registers to PWM as that is the default.
    for (int i = 0x00; i <= 0xBF; i++) {
        IS31FL3737_write_register(addr, i, 0x00);
    }

    // Unlock the command register.
    IS31FL3737_write_register(addr, ISSI_COMMANDREGISTER_WRITELOCK, 0xC5);

    // Select PG3
    IS31FL3737_write_register(addr, ISSI_COMMANDREGISTER, ISSI_PAGE_FUNCTION);
    // Set global current to maximum.
    IS31FL3737_write_register(addr, ISSI_REG_GLOBALCURRENT, 0xFF);
    // Disable software shutdown.
    IS31FL3737_write_register(addr, ISSI_REG_CONFIGURATION, 0x01);

// Wait 10ms to ensure the device has woken up.
#ifdef __AVR__
    _delay_ms(10);
#else
    wait_ms(10);
#endif
}