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
 int GPPUA ; 
 int /*<<< orphan*/  I2C_ADDR_WRITE ; 
 int IODIRA ; 
 int /*<<< orphan*/  _delay_ms (int) ; 
 int /*<<< orphan*/  i2c_init () ; 
 int i2c_initialized ; 
 int i2c_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_stop () ; 
 int i2c_write (int) ; 
 int mcp23018_status ; 

uint8_t init_mcp23018(void) {
    mcp23018_status = 0x20;

    /* I2C subsystem */

    if (i2c_initialized == 0) {
        i2c_init();  // on pins D(1,0)
        i2c_initialized = true;
        _delay_ms(1000);
    }

    /* B Pins are Row, A pins are Columns 
       Set them to output */
    mcp23018_status = i2c_start(I2C_ADDR_WRITE);    if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(IODIRA);            if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0b11111111);        if (mcp23018_status) goto out;
    /* Now write to IODIRB */
    mcp23018_status = i2c_write(0b00000000);        if (mcp23018_status) goto out;
    i2c_stop();

    mcp23018_status = i2c_start(I2C_ADDR_WRITE);    if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(GPPUA);             if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0b11111111);        if (mcp23018_status) goto out;
    /* Now write to GPPUB */
    mcp23018_status = i2c_write(0b00000000);        if (mcp23018_status) goto out;

out:
    i2c_stop();

    return mcp23018_status;
}