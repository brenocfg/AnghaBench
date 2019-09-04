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
struct regulator_desc {char* name; char* supply_name; int /*<<< orphan*/  owner; int /*<<< orphan*/  vsel_mask; int /*<<< orphan*/  vsel_reg; int /*<<< orphan*/  uV_step; int /*<<< orphan*/  min_uV; int /*<<< orphan*/  enable_mask; int /*<<< orphan*/  enable_reg; int /*<<< orphan*/  n_voltages; int /*<<< orphan*/  type; int /*<<< orphan*/ * ops; } ;
struct regulator_config {int dummy; } ;
struct fan53555_device_info {int /*<<< orphan*/  rdev; struct regulator_desc desc; int /*<<< orphan*/  dev; int /*<<< orphan*/  vol_reg; int /*<<< orphan*/  vsel_step; int /*<<< orphan*/  vsel_min; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAN53555_NVOLTAGES ; 
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REGULATOR_VOLTAGE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  VSEL_BUCK_EN ; 
 int /*<<< orphan*/  VSEL_NSEL_MASK ; 
 int /*<<< orphan*/  devm_regulator_register (int /*<<< orphan*/ ,struct regulator_desc*,struct regulator_config*) ; 
 int /*<<< orphan*/  fan53555_regulator_ops ; 

__attribute__((used)) static int fan53555_regulator_register(struct fan53555_device_info *di,
			struct regulator_config *config)
{
	struct regulator_desc *rdesc = &di->desc;

	rdesc->name = "fan53555-reg";
	rdesc->supply_name = "vin";
	rdesc->ops = &fan53555_regulator_ops;
	rdesc->type = REGULATOR_VOLTAGE;
	rdesc->n_voltages = FAN53555_NVOLTAGES;
	rdesc->enable_reg = di->vol_reg;
	rdesc->enable_mask = VSEL_BUCK_EN;
	rdesc->min_uV = di->vsel_min;
	rdesc->uV_step = di->vsel_step;
	rdesc->vsel_reg = di->vol_reg;
	rdesc->vsel_mask = VSEL_NSEL_MASK;
	rdesc->owner = THIS_MODULE;

	di->rdev = devm_regulator_register(di->dev, &di->desc, config);
	return PTR_ERR_OR_ZERO(di->rdev);
}