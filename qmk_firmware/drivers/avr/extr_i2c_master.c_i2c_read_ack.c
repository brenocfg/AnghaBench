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
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_STATUS_TIMEOUT ; 
 scalar_t__ I2C_TIMEOUT_INFINITE ; 
 int TWCR ; 
 int /*<<< orphan*/  TWDR ; 
 int TWEA ; 
 int TWEN ; 
 int TWINT ; 
 scalar_t__ timer_read () ; 

int16_t i2c_read_ack(uint16_t timeout) {
    // start TWI module and acknowledge data after reception
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);

    uint16_t timeout_timer = timer_read();
    while (!(TWCR & (1 << TWINT))) {
        if ((timeout != I2C_TIMEOUT_INFINITE) && ((timer_read() - timeout_timer) >= timeout)) {
            return I2C_STATUS_TIMEOUT;
        }
    }

    // return received data from TWDR
    return TWDR;
}