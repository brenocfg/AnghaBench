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
struct regulator_dev {int /*<<< orphan*/  regmap; TYPE_1__* constraints; } ;
struct chg_reg_data {unsigned int linear_mask; unsigned int min_sel; unsigned int uA_step; int /*<<< orphan*/  linear_reg; } ;
struct TYPE_2__ {unsigned int min_uA; unsigned int max_uA; } ;

/* Variables and functions */
 int EINVAL ; 
 struct chg_reg_data* rdev_get_drvdata (struct regulator_dev*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int max77693_chg_get_current_limit(struct regulator_dev *rdev)
{
	const struct chg_reg_data *reg_data = rdev_get_drvdata(rdev);
	unsigned int chg_min_uA = rdev->constraints->min_uA;
	unsigned int chg_max_uA = rdev->constraints->max_uA;
	unsigned int reg, sel;
	unsigned int val;
	int ret;

	ret = regmap_read(rdev->regmap, reg_data->linear_reg, &reg);
	if (ret < 0)
		return ret;

	sel = reg & reg_data->linear_mask;

	/* the first four codes for charger current are all 60mA */
	if (sel <= reg_data->min_sel)
		sel = 0;
	else
		sel -= reg_data->min_sel;

	val = chg_min_uA + reg_data->uA_step * sel;
	if (val > chg_max_uA)
		return -EINVAL;

	return val;
}