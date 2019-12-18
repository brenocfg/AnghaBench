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
typedef  int msg_t ;
typedef  int /*<<< orphan*/  i2c_status_t ;

/* Variables and functions */
#define  I2C_NO_ERROR 129 
 int /*<<< orphan*/  I2C_STATUS_ERROR ; 
 int /*<<< orphan*/  I2C_STATUS_SUCCESS ; 
 int /*<<< orphan*/  I2C_STATUS_TIMEOUT ; 
#define  I2C_TIMEOUT 128 

__attribute__((used)) static i2c_status_t chibios_to_qmk(const msg_t* status) {
    switch (*status) {
        case I2C_NO_ERROR:
            return I2C_STATUS_SUCCESS;
        case I2C_TIMEOUT:
            return I2C_STATUS_TIMEOUT;
        // I2C_BUS_ERROR, I2C_ARBITRATION_LOST, I2C_ACK_FAILURE, I2C_OVERRUN, I2C_PEC_ERROR, I2C_SMB_ALERT
        default:
            return I2C_STATUS_ERROR;
    }
}