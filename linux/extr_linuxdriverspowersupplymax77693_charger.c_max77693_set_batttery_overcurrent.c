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
 int /*<<< orphan*/  CHG_CNFG_12_B2SOVRC_MASK ; 
 unsigned int CHG_CNFG_12_B2SOVRC_SHIFT ; 
 int EINVAL ; 
 int /*<<< orphan*/  MAX77693_CHG_REG_CHG_CNFG_12 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int max77693_set_batttery_overcurrent(struct max77693_charger *chg,
		unsigned int uamp)
{
	unsigned int data;

	if (uamp && (uamp < 2000000 || uamp > 3500000)) {
		dev_err(chg->dev, "Wrong value for battery overcurrent\n");
		return -EINVAL;
	}

	if (uamp)
		data = ((uamp - 2000000) / 250000) + 1;
	else
		data = 0; /* disable */

	data <<= CHG_CNFG_12_B2SOVRC_SHIFT;

	dev_dbg(chg->dev, "Battery overcurrent: %u (0x%x)\n", uamp, data);

	return regmap_update_bits(chg->max77693->regmap,
			MAX77693_CHG_REG_CHG_CNFG_12,
			CHG_CNFG_12_B2SOVRC_MASK, data);
}