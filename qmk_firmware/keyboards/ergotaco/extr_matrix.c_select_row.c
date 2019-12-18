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
 int /*<<< orphan*/  COL10 ; 
 int /*<<< orphan*/  COL11 ; 
 int /*<<< orphan*/  COL6 ; 
 int /*<<< orphan*/  COL7 ; 
 int /*<<< orphan*/  COL8 ; 
 int /*<<< orphan*/  COL9 ; 
 int /*<<< orphan*/  DDRB ; 
 int /*<<< orphan*/  DDRD ; 
 int /*<<< orphan*/  ERGODOX_EZ_I2C_TIMEOUT ; 
 int GPIOA ; 
 int /*<<< orphan*/  I2C_ADDR_WRITE ; 
 int /*<<< orphan*/  PORTB ; 
 int /*<<< orphan*/  PORTD ; 
 scalar_t__ i2c_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_stop () ; 
 scalar_t__ i2c_write (int,int /*<<< orphan*/ ) ; 
 scalar_t__ mcp23018_status ; 

__attribute__((used)) static void select_row(uint8_t row)
{
    if (row < 6) {
        // select on mcp23018
        if (mcp23018_status) { // do nothing on error
			// Read using bitmask
        } else { // set active row low  : 0 // set other rows hi-Z : 1
            mcp23018_status = i2c_start(I2C_ADDR_WRITE, ERGODOX_EZ_I2C_TIMEOUT);        if (mcp23018_status) goto out;
            mcp23018_status = i2c_write(GPIOA, ERGODOX_EZ_I2C_TIMEOUT);                 if (mcp23018_status) goto out;
            mcp23018_status = i2c_write(~(1<<row), ERGODOX_EZ_I2C_TIMEOUT);      		if (mcp23018_status) goto out;
        out:
            i2c_stop();
        }
    } else {
        // Output low(DDR:1, PORT:0) to select
        switch (row) {
            case 6:
                DDRB  |= COL6;
                PORTB &= ~COL6;
                break;
            case 7:
                DDRB  |= COL7;
                PORTB &= ~COL7;
                break;
            case 8:
                DDRB  |= COL8;
                PORTB &= ~COL8;
                break;
            case 9:
                DDRB  |= COL9;
                PORTB &= ~COL9;
                break;
            case 10:
                DDRD  |= COL10;
                PORTD &= ~COL10;
                break;
            case 11:
                DDRD  |= COL11;
                PORTD &= ~COL11;
                break;
        }
    }
}