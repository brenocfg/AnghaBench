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
struct bq2415x_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int bq2415x_i2c_read (struct bq2415x_device*,int) ; 
 int bq2415x_i2c_write (struct bq2415x_device*,int,int) ; 

__attribute__((used)) static int bq2415x_i2c_write_mask(struct bq2415x_device *bq, u8 reg, u8 val,
				  u8 mask, u8 shift)
{
	int ret;

	if (shift > 8)
		return -EINVAL;

	ret = bq2415x_i2c_read(bq, reg);
	if (ret < 0)
		return ret;

	ret &= ~mask;
	ret |= val << shift;

	return bq2415x_i2c_write(bq, reg, ret);
}