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
struct da9210 {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 unsigned int DA9210_BUCK_ILIM_MASK ; 
 unsigned int DA9210_BUCK_ILIM_SHIFT ; 
 int /*<<< orphan*/  DA9210_REG_BUCK_ILIM ; 
 int* da9210_buck_limits ; 
 struct da9210* rdev_get_drvdata (struct regulator_dev*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int da9210_get_current_limit(struct regulator_dev *rdev)
{
	struct da9210 *chip = rdev_get_drvdata(rdev);
	unsigned int data;
	unsigned int sel;
	int ret;

	ret = regmap_read(chip->regmap, DA9210_REG_BUCK_ILIM, &data);
	if (ret < 0)
		return ret;

	/* select one of 16 values: 0000 (1600mA) to 1111 (4600mA) */
	sel = (data & DA9210_BUCK_ILIM_MASK) >> DA9210_BUCK_ILIM_SHIFT;

	return da9210_buck_limits[sel];
}