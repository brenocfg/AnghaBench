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
typedef  int uint16_t ;
typedef  scalar_t__ i2c_status_t ;

/* Variables and functions */
 scalar_t__ I2C_STATUS_SUCCESS ; 
 scalar_t__ i2c_read_ack (int) ; 
 scalar_t__ i2c_read_nack (int) ; 
 scalar_t__ i2c_start (int,int) ; 
 int /*<<< orphan*/  i2c_stop () ; 
 scalar_t__ i2c_write (int,int) ; 

i2c_status_t i2c_readReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length, uint16_t timeout) {
    i2c_status_t status = i2c_start(devaddr, timeout);
    if (status < 0) {
        goto error;
    }

    status = i2c_write(regaddr, timeout);
    if (status < 0) {
        goto error;
    }

    status = i2c_start(devaddr | 0x01, timeout);

    for (uint16_t i = 0; i < (length - 1) && status >= 0; i++) {
        status = i2c_read_ack(timeout);
        if (status >= 0) {
            data[i] = status;
        }
    }

    if (status >= 0) {
        status = i2c_read_nack(timeout);
        if (status >= 0) {
            data[(length - 1)] = status;
        }
    }

error:
    i2c_stop();

    return (status < 0) ? status : I2C_STATUS_SUCCESS;
}