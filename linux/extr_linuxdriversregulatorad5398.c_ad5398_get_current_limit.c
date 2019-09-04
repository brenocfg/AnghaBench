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
struct regulator_dev {int dummy; } ;
struct i2c_client {int dummy; } ;
struct ad5398_chip_info {unsigned short current_mask; unsigned short current_offset; struct i2c_client* client; } ;

/* Variables and functions */
 int ad5398_calc_current (struct ad5398_chip_info*,int) ; 
 int ad5398_read_reg (struct i2c_client*,unsigned short*) ; 
 struct ad5398_chip_info* rdev_get_drvdata (struct regulator_dev*) ; 

__attribute__((used)) static int ad5398_get_current_limit(struct regulator_dev *rdev)
{
	struct ad5398_chip_info *chip = rdev_get_drvdata(rdev);
	struct i2c_client *client = chip->client;
	unsigned short data;
	int ret;

	ret = ad5398_read_reg(client, &data);
	if (ret < 0)
		return ret;

	ret = (data & chip->current_mask) >> chip->current_offset;

	return ad5398_calc_current(chip, ret);
}