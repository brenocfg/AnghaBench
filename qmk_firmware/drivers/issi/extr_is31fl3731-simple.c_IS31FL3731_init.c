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
 int /*<<< orphan*/  IS31FL3731_write_register (int /*<<< orphan*/ ,int,int) ; 
 int ISSI_BANK_FUNCTIONREG ; 
 int ISSI_COMMANDREGISTER ; 
 int ISSI_REG_AUDIOSYNC ; 
 int ISSI_REG_CONFIG ; 
 int ISSI_REG_CONFIG_PICTUREMODE ; 
 int ISSI_REG_PICTUREFRAME ; 
 int ISSI_REG_SHUTDOWN ; 
 int /*<<< orphan*/  wait_ms (int) ; 

void IS31FL3731_init(uint8_t addr) {
    // In order to avoid the LEDs being driven with garbage data
    // in the LED driver's PWM registers, first enable software shutdown,
    // then set up the mode and other settings, clear the PWM registers,
    // then disable software shutdown.

    // select "function register" bank
    IS31FL3731_write_register(addr, ISSI_COMMANDREGISTER, ISSI_BANK_FUNCTIONREG);

    // enable software shutdown
    IS31FL3731_write_register(addr, ISSI_REG_SHUTDOWN, 0x00);
    // this delay was copied from other drivers, might not be needed
    wait_ms(10);

    // picture mode
    IS31FL3731_write_register(addr, ISSI_REG_CONFIG, ISSI_REG_CONFIG_PICTUREMODE);
    // display frame 0
    IS31FL3731_write_register(addr, ISSI_REG_PICTUREFRAME, 0x00);
    // audio sync off
    IS31FL3731_write_register(addr, ISSI_REG_AUDIOSYNC, 0x00);

    // select bank 0
    IS31FL3731_write_register(addr, ISSI_COMMANDREGISTER, 0);

    // turn off all LEDs in the LED control register
    for (int i = 0x00; i <= 0x11; i++) {
        IS31FL3731_write_register(addr, i, 0x00);
    }

    // turn off all LEDs in the blink control register (not really needed)
    for (int i = 0x12; i <= 0x23; i++) {
        IS31FL3731_write_register(addr, i, 0x00);
    }

    // set PWM on all LEDs to 0
    for (int i = 0x24; i <= 0xB3; i++) {
        IS31FL3731_write_register(addr, i, 0x00);
    }

    // select "function register" bank
    IS31FL3731_write_register(addr, ISSI_COMMANDREGISTER, ISSI_BANK_FUNCTIONREG);

    // disable software shutdown
    IS31FL3731_write_register(addr, ISSI_REG_SHUTDOWN, 0x01);

    // select bank 0 and leave it selected.
    // most usage after initialization is just writing PWM buffers in bank 0
    // as there's not much point in double-buffering
    IS31FL3731_write_register(addr, ISSI_COMMANDREGISTER, 0);
}