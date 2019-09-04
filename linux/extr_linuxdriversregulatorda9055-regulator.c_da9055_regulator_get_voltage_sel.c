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
struct regulator_dev {int dummy; } ;
struct da9055_volt_reg {int v_mask; int /*<<< orphan*/  reg_b; int /*<<< orphan*/  reg_a; } ;
struct TYPE_2__ {int sel_mask; int /*<<< orphan*/  reg; } ;
struct da9055_regulator_info {TYPE_1__ conf; struct da9055_volt_reg volt; } ;
struct da9055_regulator {int /*<<< orphan*/  da9055; struct da9055_regulator_info* info; } ;

/* Variables and functions */
 int DA9055_REGUALTOR_SET_A ; 
 int da9055_reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct da9055_regulator* rdev_get_drvdata (struct regulator_dev*) ; 

__attribute__((used)) static int da9055_regulator_get_voltage_sel(struct regulator_dev *rdev)
{
	struct da9055_regulator *regulator = rdev_get_drvdata(rdev);
	struct da9055_regulator_info *info = regulator->info;
	struct da9055_volt_reg volt = info->volt;
	int ret, sel;

	/*
	 * There are two voltage register set A & B for voltage ramping but
	 * either one of then can be active therefore we first determine
	 * the active register set.
	 */
	ret = da9055_reg_read(regulator->da9055, info->conf.reg);
	if (ret < 0)
		return ret;

	ret &= info->conf.sel_mask;

	/* Get the voltage for the active register set A/B */
	if (ret == DA9055_REGUALTOR_SET_A)
		ret = da9055_reg_read(regulator->da9055, volt.reg_a);
	else
		ret = da9055_reg_read(regulator->da9055, volt.reg_b);

	if (ret < 0)
		return ret;

	sel = (ret & volt.v_mask);
	return sel;
}