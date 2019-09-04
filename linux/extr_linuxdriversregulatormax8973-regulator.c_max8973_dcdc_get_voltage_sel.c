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
struct max8973_chip {int /*<<< orphan*/  curr_vout_reg; int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 unsigned int MAX8973_VOUT_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 struct max8973_chip* rdev_get_drvdata (struct regulator_dev*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int max8973_dcdc_get_voltage_sel(struct regulator_dev *rdev)
{
	struct max8973_chip *max = rdev_get_drvdata(rdev);
	unsigned int data;
	int ret;

	ret = regmap_read(max->regmap, max->curr_vout_reg, &data);
	if (ret < 0) {
		dev_err(max->dev, "register %d read failed, err = %d\n",
			max->curr_vout_reg, ret);
		return ret;
	}
	return data & MAX8973_VOUT_MASK;
}