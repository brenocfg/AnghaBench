#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rk808_regulator_data {struct gpio_desc** dvs_gpio; } ;
struct regulator_dev {int /*<<< orphan*/  regmap; TYPE_1__* desc; } ;
struct gpio_desc {int dummy; } ;
struct TYPE_2__ {unsigned int vsel_reg; unsigned int vsel_mask; } ;

/* Variables and functions */
 unsigned int RK808_DVS_REG_OFFSET ; 
 int ffs (unsigned int) ; 
 int gpiod_get_value (struct gpio_desc*) ; 
 int /*<<< orphan*/  gpiod_set_value (struct gpio_desc*,int) ; 
 struct rk808_regulator_data* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 
 int regmap_read (int /*<<< orphan*/ ,unsigned int,unsigned int*) ; 
 int regmap_write (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int rk808_buck1_2_i2c_set_voltage_sel (struct regulator_dev*,unsigned int) ; 

__attribute__((used)) static int rk808_buck1_2_set_voltage_sel(struct regulator_dev *rdev,
					 unsigned sel)
{
	struct rk808_regulator_data *pdata = rdev_get_drvdata(rdev);
	int id = rdev_get_id(rdev);
	struct gpio_desc *gpio = pdata->dvs_gpio[id];
	unsigned int reg = rdev->desc->vsel_reg;
	unsigned old_sel;
	int ret, gpio_level;

	if (!gpio)
		return rk808_buck1_2_i2c_set_voltage_sel(rdev, sel);

	gpio_level = gpiod_get_value(gpio);
	if (gpio_level == 0) {
		reg += RK808_DVS_REG_OFFSET;
		ret = regmap_read(rdev->regmap, rdev->desc->vsel_reg, &old_sel);
	} else {
		ret = regmap_read(rdev->regmap,
				  reg + RK808_DVS_REG_OFFSET,
				  &old_sel);
	}

	if (ret != 0)
		return ret;

	sel <<= ffs(rdev->desc->vsel_mask) - 1;
	sel |= old_sel & ~rdev->desc->vsel_mask;

	ret = regmap_write(rdev->regmap, reg, sel);
	if (ret)
		return ret;

	gpiod_set_value(gpio, !gpio_level);

	return ret;
}