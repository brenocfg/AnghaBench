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
struct regulator_dev {int /*<<< orphan*/  regmap; } ;
struct pv88080_regulator {int n_current_limits; int* current_limits; int /*<<< orphan*/  limit_mask; int /*<<< orphan*/  limit_reg; } ;

/* Variables and functions */
 int EINVAL ; 
 int PV88080_BUCK1_ILIM_SHIFT ; 
 struct pv88080_regulator* rdev_get_drvdata (struct regulator_dev*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pv88080_set_current_limit(struct regulator_dev *rdev, int min,
				    int max)
{
	struct pv88080_regulator *info = rdev_get_drvdata(rdev);
	int i;

	/* search for closest to maximum */
	for (i = info->n_current_limits; i >= 0; i--) {
		if (min <= info->current_limits[i]
			&& max >= info->current_limits[i]) {
				return regmap_update_bits(rdev->regmap,
					info->limit_reg,
					info->limit_mask,
					i << PV88080_BUCK1_ILIM_SHIFT);
		}
	}

	return -EINVAL;
}