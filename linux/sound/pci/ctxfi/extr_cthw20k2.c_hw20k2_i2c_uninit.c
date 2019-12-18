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
struct hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_ADDRESS_SLAD ; 
 int /*<<< orphan*/  I2C_IF_ADDRESS ; 
 int /*<<< orphan*/  I2C_IF_STATUS ; 
 int /*<<< orphan*/  I2C_STATUS_DCM ; 
 int hw20k2_i2c_lock_chip (struct hw*) ; 
 unsigned int hw_read_20kx (struct hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_write_20kx (struct hw*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  set_field (unsigned int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hw20k2_i2c_uninit(struct hw *hw)
{
	unsigned int i2c_status;
	unsigned int i2c_addr;

	i2c_addr = 0;
	set_field(&i2c_addr, I2C_ADDRESS_SLAD, 0x57); /* I2C id */

	hw_write_20kx(hw, I2C_IF_ADDRESS, i2c_addr);

	i2c_status = hw_read_20kx(hw, I2C_IF_STATUS);

	set_field(&i2c_status, I2C_STATUS_DCM, 0); /* I2C mode */

	hw_write_20kx(hw, I2C_IF_STATUS, i2c_status);

	return hw20k2_i2c_lock_chip(hw);
}