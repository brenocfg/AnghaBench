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
struct chg_reg_data {int uA_step; int /*<<< orphan*/  linear_reg; scalar_t__ min_sel; } ;
struct TYPE_2__ {unsigned int min_uA; } ;

/* Variables and functions */
 int EINVAL ; 
 struct chg_reg_data* rdev_get_drvdata (struct regulator_dev*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int max77693_chg_set_current_limit(struct regulator_dev *rdev,
						int min_uA, int max_uA)
{
	const struct chg_reg_data *reg_data = rdev_get_drvdata(rdev);
	unsigned int chg_min_uA = rdev->constraints->min_uA;
	int sel = 0;

	while (chg_min_uA + reg_data->uA_step * sel < min_uA)
		sel++;

	if (chg_min_uA + reg_data->uA_step * sel > max_uA)
		return -EINVAL;

	/* the first four codes for charger current are all 60mA */
	sel += reg_data->min_sel;

	return regmap_write(rdev->regmap, reg_data->linear_reg, sel);
}