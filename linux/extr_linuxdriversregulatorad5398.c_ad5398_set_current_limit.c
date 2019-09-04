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
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct ad5398_chip_info {unsigned int max_uA; unsigned int min_uA; int current_level; unsigned int current_offset; unsigned int current_mask; struct i2c_client* client; } ;

/* Variables and functions */
 unsigned short AD5398_CURRENT_EN_MASK ; 
 unsigned int DIV_ROUND_UP (int,unsigned int) ; 
 int EINVAL ; 
 int ad5398_calc_current (struct ad5398_chip_info*,unsigned int) ; 
 int ad5398_read_reg (struct i2c_client*,unsigned short*) ; 
 int ad5398_write_reg (struct i2c_client*,unsigned short) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 struct ad5398_chip_info* rdev_get_drvdata (struct regulator_dev*) ; 

__attribute__((used)) static int ad5398_set_current_limit(struct regulator_dev *rdev, int min_uA, int max_uA)
{
	struct ad5398_chip_info *chip = rdev_get_drvdata(rdev);
	struct i2c_client *client = chip->client;
	unsigned range_uA = chip->max_uA - chip->min_uA;
	unsigned selector;
	unsigned short data;
	int ret;

	if (min_uA < chip->min_uA)
		min_uA = chip->min_uA;
	if (max_uA > chip->max_uA)
		max_uA = chip->max_uA;

	if (min_uA > chip->max_uA || max_uA < chip->min_uA)
		return -EINVAL;

	selector = DIV_ROUND_UP((min_uA - chip->min_uA) * chip->current_level,
				range_uA);
	if (ad5398_calc_current(chip, selector) > max_uA)
		return -EINVAL;

	dev_dbg(&client->dev, "changing current %duA\n",
		ad5398_calc_current(chip, selector));

	/* read chip enable bit */
	ret = ad5398_read_reg(client, &data);
	if (ret < 0)
		return ret;

	/* prepare register data */
	selector = (selector << chip->current_offset) & chip->current_mask;
	data = (unsigned short)selector | (data & AD5398_CURRENT_EN_MASK);

	/* write the new current value back as well as enable bit */
	ret = ad5398_write_reg(client, data);

	return ret;
}