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

__attribute__((used)) static void select_row(uint8_t row)
{
    if (row < 8) {
        // select on mcp23018
        if (mcp23018_status) { // if there was an error
            // do nothing
        } else {
            // set active row low  : 0
            // set other rows hi-Z : 1
            mcp23018_status = i2c_start(I2C_ADDR_WRITE, I2C_TIMEOUT);                          if (mcp23018_status) goto out;
            mcp23018_status = i2c_write(GPIOA, I2C_TIMEOUT);                                   if (mcp23018_status) goto out;
            mcp23018_status = i2c_write( 0xFF & ~(1<<row) & ~(0<<8), I2C_TIMEOUT);             if (mcp23018_status) goto out;
        out:
            i2c_stop();
        }
    } else {
        // select on teensy
        // Output low(DDR:1, PORT:0) to select
        switch (row) {
            case 8:
                DDRB  |= (1<<0);
                PORTB &= ~(1<<0);
                break;
            case 9:
                DDRB  |= (1<<1);
                PORTB &= ~(1<<1);
                break;
            case 10:
                DDRB  |= (1<<2);
                PORTB &= ~(1<<2);
                break;
            case 11:
                DDRB  |= (1<<3);
                PORTB &= ~(1<<3);
                break;
            case 12:
                DDRD  |= (1<<2);
                PORTD &= ~(1<<3);
                break;
            case 13:
                DDRD  |= (1<<3);
                PORTD &= ~(1<<3);
                break;
            case 14:
                DDRC  |= (1<<6);
                PORTC &= ~(1<<6);
                break;
            case 15:
                DDRC  |= (1<<7);
                PORTC &= ~(1<<7);
                break;
        }
    }
}