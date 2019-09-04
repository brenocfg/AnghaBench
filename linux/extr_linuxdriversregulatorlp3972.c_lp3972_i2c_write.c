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
typedef  int /*<<< orphan*/  u16 ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,char,int /*<<< orphan*/  const) ; 

__attribute__((used)) static int lp3972_i2c_write(struct i2c_client *i2c, char reg, int count,
	const u16 *src)
{
	if (count != 1)
		return -EIO;
	return i2c_smbus_write_byte_data(i2c, reg, *src);
}