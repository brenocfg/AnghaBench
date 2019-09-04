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
typedef  int /*<<< orphan*/  u8 ;
struct max77620_regulator_info {scalar_t__ type; int /*<<< orphan*/  cfg_addr; } ;
struct max77620_regulator {int /*<<< orphan*/  dev; int /*<<< orphan*/  rmap; struct max77620_regulator_info** rinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX77620_LDO_SLEW_RATE_MASK ; 
 scalar_t__ MAX77620_REGULATOR_TYPE_SD ; 
 int /*<<< orphan*/  MAX77620_SD_SR_MASK ; 
 unsigned int MAX77620_SD_SR_SHIFT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int max77620_set_slew_rate(struct max77620_regulator *pmic, int id,
				  int slew_rate)
{
	struct max77620_regulator_info *rinfo = pmic->rinfo[id];
	unsigned int val;
	int ret;
	u8 mask;

	if (rinfo->type == MAX77620_REGULATOR_TYPE_SD) {
		if (slew_rate <= 13750)
			val = 0;
		else if (slew_rate <= 27500)
			val = 1;
		else if (slew_rate <= 55000)
			val = 2;
		else
			val = 3;
		val <<= MAX77620_SD_SR_SHIFT;
		mask = MAX77620_SD_SR_MASK;
	} else {
		if (slew_rate <= 5000)
			val = 1;
		else
			val = 0;
		mask = MAX77620_LDO_SLEW_RATE_MASK;
	}

	ret = regmap_update_bits(pmic->rmap, rinfo->cfg_addr, mask, val);
	if (ret < 0) {
		dev_err(pmic->dev, "Regulator %d slew rate set failed: %d\n",
			id, ret);
		return ret;
	}

	return 0;
}