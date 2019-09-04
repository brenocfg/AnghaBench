#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct regulator_dev {int dummy; } ;
struct TYPE_4__ {int v_mask; int /*<<< orphan*/  reg_b; int /*<<< orphan*/  reg_a; } ;
struct TYPE_3__ {int sel_mask; int /*<<< orphan*/  reg; } ;
struct da9055_regulator_info {TYPE_2__ volt; TYPE_1__ conf; } ;
struct da9055_regulator {scalar_t__ reg_rselect; int /*<<< orphan*/  da9055; struct da9055_regulator_info* info; } ;

/* Variables and functions */
 int DA9055_REGUALTOR_SET_A ; 
 unsigned int DA9055_SEL_REG_A ; 
 scalar_t__ NO_GPIO ; 
 int da9055_reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int da9055_reg_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int) ; 
 struct da9055_regulator* rdev_get_drvdata (struct regulator_dev*) ; 

__attribute__((used)) static int da9055_regulator_set_voltage_sel(struct regulator_dev *rdev,
					    unsigned int selector)
{
	struct da9055_regulator *regulator = rdev_get_drvdata(rdev);
	struct da9055_regulator_info *info = regulator->info;
	int ret;

	/*
	 * Regulator register set A/B is not selected through GPIO therefore
	 * we use default register set A for voltage ramping.
	 */
	if (regulator->reg_rselect == NO_GPIO) {
		/* Select register set A */
		ret = da9055_reg_update(regulator->da9055, info->conf.reg,
					info->conf.sel_mask, DA9055_SEL_REG_A);
		if (ret < 0)
			return ret;

		/* Set the voltage */
		return da9055_reg_update(regulator->da9055, info->volt.reg_a,
					 info->volt.v_mask, selector);
	}

	/*
	 * Here regulator register set A/B is selected through GPIO.
	 * Therefore we first determine the selected register set A/B and
	 * then set the desired voltage for that register set A/B.
	 */
	ret = da9055_reg_read(regulator->da9055, info->conf.reg);
	if (ret < 0)
		return ret;

	ret &= info->conf.sel_mask;

	/* Set the voltage */
	if (ret == DA9055_REGUALTOR_SET_A)
		return da9055_reg_update(regulator->da9055, info->volt.reg_a,
					 info->volt.v_mask, selector);
	else
		return da9055_reg_update(regulator->da9055, info->volt.reg_b,
					 info->volt.v_mask, selector);
}