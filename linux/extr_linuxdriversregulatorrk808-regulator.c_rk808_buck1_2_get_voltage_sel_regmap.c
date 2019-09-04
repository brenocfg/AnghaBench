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
struct regulator_dev {TYPE_1__* desc; int /*<<< orphan*/  regmap; } ;
struct gpio_desc {int dummy; } ;
struct TYPE_2__ {unsigned int vsel_mask; scalar_t__ vsel_reg; } ;

/* Variables and functions */
 scalar_t__ RK808_DVS_REG_OFFSET ; 
 int ffs (unsigned int) ; 
 scalar_t__ gpiod_get_value (struct gpio_desc*) ; 
 struct rk808_regulator_data* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 
 int regmap_read (int /*<<< orphan*/ ,scalar_t__,unsigned int*) ; 
 int regulator_get_voltage_sel_regmap (struct regulator_dev*) ; 

__attribute__((used)) static int rk808_buck1_2_get_voltage_sel_regmap(struct regulator_dev *rdev)
{
	struct rk808_regulator_data *pdata = rdev_get_drvdata(rdev);
	int id = rdev_get_id(rdev);
	struct gpio_desc *gpio = pdata->dvs_gpio[id];
	unsigned int val;
	int ret;

	if (!gpio || gpiod_get_value(gpio) == 0)
		return regulator_get_voltage_sel_regmap(rdev);

	ret = regmap_read(rdev->regmap,
			  rdev->desc->vsel_reg + RK808_DVS_REG_OFFSET,
			  &val);
	if (ret != 0)
		return ret;

	val &= rdev->desc->vsel_mask;
	val >>= ffs(rdev->desc->vsel_mask) - 1;

	return val;
}