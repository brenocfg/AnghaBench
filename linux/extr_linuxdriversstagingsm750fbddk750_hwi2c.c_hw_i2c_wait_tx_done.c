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
 unsigned int HWI2C_WAIT_TIMEOUT ; 
 int /*<<< orphan*/  I2C_STATUS ; 
 int I2C_STATUS_TX ; 
 int peek32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static long hw_i2c_wait_tx_done(void)
{
	unsigned int timeout;

	/* Wait until the transfer is completed. */
	timeout = HWI2C_WAIT_TIMEOUT;
	while (!(peek32(I2C_STATUS) & I2C_STATUS_TX) && (timeout != 0))
		timeout--;

	if (timeout == 0)
		return -1;

	return 0;
}