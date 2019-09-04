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
struct pv88060_regulator {unsigned int limit_mask; int* current_limits; int /*<<< orphan*/  conf; } ;

/* Variables and functions */
 unsigned int PV88060_BUCK_ILIM_SHIFT ; 
 struct pv88060_regulator* rdev_get_drvdata (struct regulator_dev*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int pv88060_get_current_limit(struct regulator_dev *rdev)
{
	struct pv88060_regulator *info = rdev_get_drvdata(rdev);
	unsigned int data;
	int ret;

	ret = regmap_read(rdev->regmap, info->conf, &data);
	if (ret < 0)
		return ret;

	data = (data & info->limit_mask) >> PV88060_BUCK_ILIM_SHIFT;
	return info->current_limits[data];
}