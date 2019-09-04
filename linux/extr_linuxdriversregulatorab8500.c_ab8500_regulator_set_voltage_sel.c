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
typedef  int u8 ;
struct regulator_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct ab8500_regulator_info {int /*<<< orphan*/  voltage_mask; int /*<<< orphan*/  voltage_reg; int /*<<< orphan*/  voltage_bank; TYPE_1__ desc; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int abx500_mask_and_set_register_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ffs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdev_get_dev (struct regulator_dev*) ; 
 struct ab8500_regulator_info* rdev_get_drvdata (struct regulator_dev*) ; 

__attribute__((used)) static int ab8500_regulator_set_voltage_sel(struct regulator_dev *rdev,
					    unsigned selector)
{
	int ret, voltage_shift;
	struct ab8500_regulator_info *info = rdev_get_drvdata(rdev);
	u8 regval;

	if (info == NULL) {
		dev_err(rdev_get_dev(rdev), "regulator info null pointer\n");
		return -EINVAL;
	}

	voltage_shift = ffs(info->voltage_mask) - 1;

	/* set the registers for the request */
	regval = (u8)selector << voltage_shift;
	ret = abx500_mask_and_set_register_interruptible(info->dev,
			info->voltage_bank, info->voltage_reg,
			info->voltage_mask, regval);
	if (ret < 0)
		dev_err(rdev_get_dev(rdev),
		"couldn't set voltage reg for regulator\n");

	dev_vdbg(rdev_get_dev(rdev),
		"%s-set_voltage (bank, reg, mask, value): 0x%x, 0x%x, 0x%x,"
		" 0x%x\n",
		info->desc.name, info->voltage_bank, info->voltage_reg,
		info->voltage_mask, regval);

	return ret;
}