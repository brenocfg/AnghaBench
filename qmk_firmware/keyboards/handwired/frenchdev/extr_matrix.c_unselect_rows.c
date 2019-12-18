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

/* Variables and functions */
 int DDRB ; 
 int DDRC ; 
 int DDRD ; 
 int GPIOA ; 
 int /*<<< orphan*/  I2C_ADDR_WRITE ; 
 int /*<<< orphan*/  I2C_TIMEOUT ; 
 int PORTB ; 
 int PORTC ; 
 int PORTD ; 
 scalar_t__ i2c_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_stop () ; 
 scalar_t__ i2c_write (int,int /*<<< orphan*/ ) ; 
 scalar_t__ mcp23018_status ; 

__attribute__((used)) static void unselect_rows(void)
{
    // unselect on mcp23018
    if (mcp23018_status) { // if there was an error
        // do nothing
    } else {
        // set all rows hi-Z : 1
        mcp23018_status = i2c_start(I2C_ADDR_WRITE, I2C_TIMEOUT);    if (mcp23018_status) goto out;
        mcp23018_status = i2c_write(GPIOA, I2C_TIMEOUT);             if (mcp23018_status) goto out;
        mcp23018_status = i2c_write( 0xFF & ~(0<<8), I2C_TIMEOUT);   if (mcp23018_status) goto out;
    out:
        i2c_stop();
    }

    // unselect on teensy
    // Hi-Z(DDR:0, PORT:0) to unselect
    DDRB  &= ~(1<<0 | 1<<1 | 1<<2 | 1<<3);
    PORTB &= ~(1<<0 | 1<<1 | 1<<2 | 1<<3);
    DDRD  &= ~(1<<2 | 1<<3);
    PORTD &= ~(1<<2 | 1<<3);
    DDRC  &= ~(1<<6 | 1<<7);
    PORTC &= ~(1<<6 | 1<<7);
}