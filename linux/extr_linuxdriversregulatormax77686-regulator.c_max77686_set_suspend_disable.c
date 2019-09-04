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
struct regulator_dev {TYPE_1__* desc; int /*<<< orphan*/  regmap; } ;
struct max77686_data {unsigned int* opmode; } ;
struct TYPE_2__ {int /*<<< orphan*/  enable_mask; int /*<<< orphan*/  enable_reg; } ;

/* Variables and functions */
 unsigned int MAX77686_OFF_PWRREQ ; 
 unsigned int max77686_get_opmode_shift (int) ; 
 struct max77686_data* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int max77686_set_suspend_disable(struct regulator_dev *rdev)
{
	unsigned int val, shift;
	struct max77686_data *max77686 = rdev_get_drvdata(rdev);
	int ret, id = rdev_get_id(rdev);

	shift = max77686_get_opmode_shift(id);
	val = MAX77686_OFF_PWRREQ;

	ret = regmap_update_bits(rdev->regmap, rdev->desc->enable_reg,
				 rdev->desc->enable_mask, val << shift);
	if (ret)
		return ret;

	max77686->opmode[id] = val;
	return 0;
}