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
struct max77693_charger {TYPE_1__* max77693; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHG_CNFG_04_MINVSYS_MASK ; 
 unsigned int CHG_CNFG_04_MINVSYS_SHIFT ; 
 int EINVAL ; 
 int /*<<< orphan*/  MAX77693_CHG_REG_CHG_CNFG_04 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int max77693_set_min_system_volt(struct max77693_charger *chg,
		unsigned int uvolt)
{
	unsigned int data;

	if (uvolt < 3000000 || uvolt > 3700000) {
		dev_err(chg->dev, "Wrong value for minimum system regulation voltage\n");
		return -EINVAL;
	}

	data = (uvolt - 3000000) / 100000;

	data <<= CHG_CNFG_04_MINVSYS_SHIFT;

	dev_dbg(chg->dev, "Minimum system regulation voltage: %u (0x%x)\n",
			uvolt, data);

	return regmap_update_bits(chg->max77693->regmap,
			MAX77693_CHG_REG_CHG_CNFG_04,
			CHG_CNFG_04_MINVSYS_MASK, data);
}