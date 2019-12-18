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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 int PORTC ; 
 scalar_t__ TWBR ; 
 scalar_t__ TWBR_val ; 
 int TWCR ; 
 int TWEA ; 
 int TWEN ; 
 int TWIE ; 
 scalar_t__ TWSR ; 

void i2c_init(void) {
    TWSR = 0; /* no prescaler */
    TWBR = (uint8_t)TWBR_val;

#ifdef __AVR_ATmega32A__
    // set pull-up resistors on I2C bus pins
    PORTC |= 0b11;

    // enable TWI (two-wire interface)
    TWCR |= (1 << TWEN);

    // enable TWI interrupt and slave address ACK
    TWCR |= (1 << TWIE);
    TWCR |= (1 << TWEA);
#endif
}