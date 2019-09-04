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
struct TYPE_2__ {int ramp_delay; } ;
struct max77620_regulator_info {int type; TYPE_1__ desc; int /*<<< orphan*/  cfg_addr; } ;
struct max77620_regulator {int /*<<< orphan*/  dev; int /*<<< orphan*/  rmap; struct max77620_regulator_info** rinfo; } ;

/* Variables and functions */
#define  MAX77620_REGULATOR_TYPE_SD 128 
 unsigned int MAX77620_SD_SR_SHIFT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int max77620_read_slew_rate(struct max77620_regulator *pmic, int id)
{
	struct max77620_regulator_info *rinfo = pmic->rinfo[id];
	unsigned int rval;
	int slew_rate;
	int ret;

	ret = regmap_read(pmic->rmap, rinfo->cfg_addr, &rval);
	if (ret < 0) {
		dev_err(pmic->dev, "Register 0x%02x read failed: %d\n",
			rinfo->cfg_addr, ret);
		return ret;
	}

	switch (rinfo->type) {
	case MAX77620_REGULATOR_TYPE_SD:
		slew_rate = (rval >> MAX77620_SD_SR_SHIFT) & 0x3;
		switch (slew_rate) {
		case 0:
			slew_rate = 13750;
			break;
		case 1:
			slew_rate = 27500;
			break;
		case 2:
			slew_rate = 55000;
			break;
		case 3:
			slew_rate = 100000;
			break;
		}
		rinfo->desc.ramp_delay = slew_rate;
		break;
	default:
		slew_rate = rval & 0x1;
		switch (slew_rate) {
		case 0:
			slew_rate = 100000;
			break;
		case 1:
			slew_rate = 5000;
			break;
		}
		rinfo->desc.ramp_delay = slew_rate;
		break;
	}

	return 0;
}