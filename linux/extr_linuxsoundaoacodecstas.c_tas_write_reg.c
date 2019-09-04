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
typedef  int u8 ;
struct tas {int /*<<< orphan*/  i2c; } ;

/* Variables and functions */
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int,int) ; 
 int i2c_smbus_write_i2c_block_data (int /*<<< orphan*/ ,int,int,int*) ; 

__attribute__((used)) static inline int tas_write_reg(struct tas *tas, u8 reg, u8 len, u8 *data)
{
	if (len == 1)
		return i2c_smbus_write_byte_data(tas->i2c, reg, *data);
	else
		return i2c_smbus_write_i2c_block_data(tas->i2c, reg, len, data);
}