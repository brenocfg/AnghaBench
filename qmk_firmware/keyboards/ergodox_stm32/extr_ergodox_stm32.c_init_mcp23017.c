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
 int /*<<< orphan*/  I2C_ADDR ; 
 int /*<<< orphan*/  I2C_GPIOA ; 
 int /*<<< orphan*/  I2C_GPPUB ; 
 int /*<<< orphan*/  I2C_IODIRA ; 
 int /*<<< orphan*/  i2c_init () ; 
 int i2c_initializied ; 
 int i2c_writeReg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int) ; 
 int mcp23017_status ; 

uint8_t init_mcp23017(void) {
    if (!i2c_initializied) {
        i2c_init();
        i2c_initializied = 1;
    }

    uint8_t data[2];
    data[0] = 0x0;
    data[1] = 0b00111111;
    mcp23017_status = i2c_writeReg(I2C_ADDR, I2C_IODIRA, data, 2, 50000);
    if (mcp23017_status) goto out;
    data[0] = 0xFFU;
    mcp23017_status = i2c_writeReg(I2C_ADDR, I2C_GPIOA, data, 1, 5000);
    if (mcp23017_status) goto out;
    mcp23017_status = i2c_writeReg(I2C_ADDR, I2C_GPPUB, data+1, 1, 2);
    if (mcp23017_status) goto out;

 out:
    return mcp23017_status;
    // i2c_readReg(I2C_ADDR, );
}