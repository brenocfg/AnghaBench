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
typedef  int matrix_row_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERGODOX_EZ_I2C_TIMEOUT ; 
 int /*<<< orphan*/  GPIOB ; 
 int /*<<< orphan*/  I2C_ADDR_READ ; 
 int /*<<< orphan*/  I2C_ADDR_WRITE ; 
 scalar_t__ I2C_STATUS_SUCCESS ; 
 int PINF ; 
 int ROW1 ; 
 scalar_t__ i2c_read_nack (int /*<<< orphan*/ ) ; 
 scalar_t__ i2c_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_stop () ; 
 scalar_t__ i2c_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mcp23018_status ; 
 int /*<<< orphan*/  xprintf (char*,int) ; 

__attribute__((used)) static matrix_row_t read_cols(uint8_t row)
{
    if (row < 6) {
        if (mcp23018_status) { // if there was an error
            return 0;
        } else {
            uint8_t data = 0;
            mcp23018_status = i2c_start(I2C_ADDR_WRITE, ERGODOX_EZ_I2C_TIMEOUT);    if (mcp23018_status) goto out;
            mcp23018_status = i2c_write(GPIOB, ERGODOX_EZ_I2C_TIMEOUT);             if (mcp23018_status) goto out;
            mcp23018_status = i2c_start(I2C_ADDR_READ, ERGODOX_EZ_I2C_TIMEOUT);     if (mcp23018_status) goto out;
            mcp23018_status = i2c_read_nack(ERGODOX_EZ_I2C_TIMEOUT);                if (mcp23018_status < 0) goto out;
            data = (~((uint8_t)mcp23018_status) >> 2) & 0x01 ;
            mcp23018_status = I2C_STATUS_SUCCESS;
        out:
            i2c_stop();

#ifdef DEBUG_MATRIX
            if (data != 0x00) xprintf("I2C: %d\n", data);
#endif
            return data;
        }
    } else {
		// Read using bitmask
        return ~((((PINF & ROW1) >> 5)) & 0x1);
    }
}