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
struct max77693_charger {TYPE_1__* max77693; } ;
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHG_CNFG_03_TOITH_MASK ; 
 unsigned int CHG_CNFG_03_TOITH_SHIFT ; 
 int EINVAL ; 
 int /*<<< orphan*/  MAX77693_CHG_REG_CHG_CNFG_03 ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int max77693_set_top_off_threshold_current(struct max77693_charger *chg,
		unsigned long uamp)
{
	unsigned int data;

	if (uamp < 100000 || uamp > 350000)
		return -EINVAL;

	if (uamp <= 200000)
		data = (uamp - 100000) / 25000;
	else
		/* (200000, 350000> */
		data = uamp / 50000;

	data <<= CHG_CNFG_03_TOITH_SHIFT;

	return regmap_update_bits(chg->max77693->regmap,
			MAX77693_CHG_REG_CHG_CNFG_03,
			CHG_CNFG_03_TOITH_MASK, data);
}