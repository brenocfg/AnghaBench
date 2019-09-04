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
struct regulator_dev {TYPE_1__* desc; } ;
struct max8649_regulator_info {int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  vsel_reg; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int /*<<< orphan*/  MAX8649_RAMP ; 
 unsigned int MAX8649_RAMP_MASK ; 
 unsigned int MAX8649_VOL_MASK ; 
 struct max8649_regulator_info* rdev_get_drvdata (struct regulator_dev*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regulator_list_voltage_linear (struct regulator_dev*,unsigned char) ; 

__attribute__((used)) static int max8649_enable_time(struct regulator_dev *rdev)
{
	struct max8649_regulator_info *info = rdev_get_drvdata(rdev);
	int voltage, rate, ret;
	unsigned int val;

	/* get voltage */
	ret = regmap_read(info->regmap, rdev->desc->vsel_reg, &val);
	if (ret != 0)
		return ret;
	val &= MAX8649_VOL_MASK;
	voltage = regulator_list_voltage_linear(rdev, (unsigned char)val);

	/* get rate */
	ret = regmap_read(info->regmap, MAX8649_RAMP, &val);
	if (ret != 0)
		return ret;
	ret = (val & MAX8649_RAMP_MASK) >> 5;
	rate = (32 * 1000) >> ret;	/* uV/uS */

	return DIV_ROUND_UP(voltage, rate);
}