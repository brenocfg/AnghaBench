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
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  i2c_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_STATUS_ERROR ; 
 int /*<<< orphan*/  I2C_STATUS_SUCCESS ; 
 int /*<<< orphan*/  I2C_STATUS_TIMEOUT ; 
 scalar_t__ I2C_TIMEOUT_INFINITE ; 
 int TWCR ; 
 scalar_t__ TWDR ; 
 int TWEN ; 
 int TWINT ; 
 int TWSTA ; 
 scalar_t__ TW_MR_SLA_ACK ; 
 scalar_t__ TW_MT_SLA_ACK ; 
 int TW_REP_START ; 
 int TW_START ; 
 int TW_STATUS ; 
 scalar_t__ timer_read () ; 

i2c_status_t i2c_start(uint8_t address, uint16_t timeout) {
    // reset TWI control register
    TWCR = 0;
    // transmit START condition
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

    uint16_t timeout_timer = timer_read();
    while (!(TWCR & (1 << TWINT))) {
        if ((timeout != I2C_TIMEOUT_INFINITE) && ((timer_read() - timeout_timer) >= timeout)) {
            return I2C_STATUS_TIMEOUT;
        }
    }

    // check if the start condition was successfully transmitted
    if (((TW_STATUS & 0xF8) != TW_START) && ((TW_STATUS & 0xF8) != TW_REP_START)) {
        return I2C_STATUS_ERROR;
    }

    // load slave address into data register
    TWDR = address;
    // start transmission of address
    TWCR = (1 << TWINT) | (1 << TWEN);

    timeout_timer = timer_read();
    while (!(TWCR & (1 << TWINT))) {
        if ((timeout != I2C_TIMEOUT_INFINITE) && ((timer_read() - timeout_timer) >= timeout)) {
            return I2C_STATUS_TIMEOUT;
        }
    }

    // check if the device has acknowledged the READ / WRITE mode
    uint8_t twst = TW_STATUS & 0xF8;
    if ((twst != TW_MT_SLA_ACK) && (twst != TW_MR_SLA_ACK)) {
        return I2C_STATUS_ERROR;
    }

    return I2C_STATUS_SUCCESS;
}