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
 int /*<<< orphan*/  I2C_ACK ; 
 int /*<<< orphan*/  I2C_NACK ; 
 scalar_t__ I2C_READ ; 
 scalar_t__ I2C_WRITE ; 
 int ROWS_PER_HAND ; 
 scalar_t__ SLAVE_I2C_ADDRESS ; 
 int /*<<< orphan*/  i2c_master_read (int /*<<< orphan*/ ) ; 
 int i2c_master_start (scalar_t__) ; 
 int /*<<< orphan*/  i2c_master_stop () ; 
 int i2c_master_write (int) ; 
 int /*<<< orphan*/  i2c_reset_state () ; 
 scalar_t__ isLeftHand ; 
 int /*<<< orphan*/ * matrix ; 

int i2c_transaction(void) {
    int slaveOffset = (isLeftHand) ? (ROWS_PER_HAND) : 0;

    int err = i2c_master_start(SLAVE_I2C_ADDRESS + I2C_WRITE);
    if (err) goto i2c_error;

    // start of matrix stored at 0x00
    err = i2c_master_write(0x00);
    if (err) goto i2c_error;

    // Start read
    err = i2c_master_start(SLAVE_I2C_ADDRESS + I2C_READ);
    if (err) goto i2c_error;

    if (!err) {
        int i;
        for (i = 0; i < ROWS_PER_HAND-1; ++i) {
            matrix[slaveOffset+i] = i2c_master_read(I2C_ACK);
        }
        matrix[slaveOffset+i] = i2c_master_read(I2C_NACK);
        i2c_master_stop();
    } else {
i2c_error: // the cable is disconnceted, or something else went wrong
        i2c_reset_state();
        return err;
    }

    return 0;
}