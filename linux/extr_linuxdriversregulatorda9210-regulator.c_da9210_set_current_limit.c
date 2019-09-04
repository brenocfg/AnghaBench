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
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  DA9210_BUCK_ILIM_MASK ; 
 unsigned int DA9210_BUCK_ILIM_SHIFT ; 
 int /*<<< orphan*/  DA9210_REG_BUCK_ILIM ; 
 int EINVAL ; 
 int* da9210_buck_limits ; 
 struct da9210* rdev_get_drvdata (struct regulator_dev*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int da9210_set_current_limit(struct regulator_dev *rdev, int min_uA,
				    int max_uA)
{
	struct da9210 *chip = rdev_get_drvdata(rdev);
	unsigned int sel;
	int i;

	/* search for closest to maximum */
	for (i = ARRAY_SIZE(da9210_buck_limits)-1; i >= 0; i--) {
		if (min_uA <= da9210_buck_limits[i] &&
		    max_uA >= da9210_buck_limits[i]) {
			sel = i;
			sel = sel << DA9210_BUCK_ILIM_SHIFT;
			return regmap_update_bits(chip->regmap,
						  DA9210_REG_BUCK_ILIM,
						  DA9210_BUCK_ILIM_MASK, sel);
		}
	}

	return -EINVAL;
}