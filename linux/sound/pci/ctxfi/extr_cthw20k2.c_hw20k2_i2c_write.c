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
typedef  int u32 ;
typedef  int u16 ;
struct hw20k2 {int addr_size; int data_size; } ;
struct hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_IF_STATUS ; 
 int /*<<< orphan*/  I2C_IF_WDATA ; 
 int /*<<< orphan*/  I2C_STATUS_BC ; 
 int /*<<< orphan*/  hw20k2_i2c_wait_data_ready (struct hw*) ; 
 unsigned int hw_read_20kx (struct hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_write_20kx (struct hw*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  set_field (unsigned int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hw20k2_i2c_write(struct hw *hw, u16 addr, u32 data)
{
	struct hw20k2 *hw20k2 = (struct hw20k2 *)hw;
	unsigned int i2c_data = (data << (hw20k2->addr_size * 8)) | addr;
	unsigned int i2c_status;

	i2c_status = hw_read_20kx(hw, I2C_IF_STATUS);

	set_field(&i2c_status, I2C_STATUS_BC,
		  (4 == (hw20k2->addr_size + hw20k2->data_size)) ?
		  0 : (hw20k2->addr_size + hw20k2->data_size));

	hw_write_20kx(hw, I2C_IF_STATUS, i2c_status);
	hw20k2_i2c_wait_data_ready(hw);
	/* Dummy write to trigger the write operation */
	hw_write_20kx(hw, I2C_IF_WDATA, 0);
	hw20k2_i2c_wait_data_ready(hw);

	/* This is the real data */
	hw_write_20kx(hw, I2C_IF_WDATA, i2c_data);
	hw20k2_i2c_wait_data_ready(hw);

	return 0;
}