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
 int /*<<< orphan*/  hw_i2c_read_data (unsigned char,int,unsigned char*) ; 
 int hw_i2c_write_data (unsigned char,int,unsigned char*) ; 

unsigned char sm750_hw_i2c_read_reg(unsigned char addr, unsigned char reg)
{
	unsigned char value = 0xFF;

	if (hw_i2c_write_data(addr, 1, &reg) == 1)
		hw_i2c_read_data(addr, 1, &value);

	return value;
}