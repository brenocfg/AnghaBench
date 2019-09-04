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
 unsigned char sw_i2c_read_byte (int) ; 
 int /*<<< orphan*/  sw_i2c_start () ; 
 int /*<<< orphan*/  sw_i2c_stop () ; 
 int /*<<< orphan*/  sw_i2c_write_byte (unsigned char) ; 

unsigned char sm750_sw_i2c_read_reg(unsigned char addr, unsigned char reg)
{
	unsigned char data;

	/* Send the Start signal */
	sw_i2c_start();

	/* Send the device address */
	sw_i2c_write_byte(addr);

	/* Send the register index */
	sw_i2c_write_byte(reg);

	/* Get the bus again and get the data from the device read address */
	sw_i2c_start();
	sw_i2c_write_byte(addr + 1);
	data = sw_i2c_read_byte(1);

	/* Stop swI2C and release the bus */
	sw_i2c_stop();

	return data;
}