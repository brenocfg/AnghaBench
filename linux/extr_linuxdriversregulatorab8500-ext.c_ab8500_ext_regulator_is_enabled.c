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
struct ab8500_ext_regulator_info {int update_mask; int update_val_lp; int update_val_hp; int /*<<< orphan*/  update_reg; int /*<<< orphan*/  update_bank; TYPE_1__ desc; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int abx500_get_register_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  rdev_get_dev (struct regulator_dev*) ; 
 struct ab8500_ext_regulator_info* rdev_get_drvdata (struct regulator_dev*) ; 

__attribute__((used)) static int ab8500_ext_regulator_is_enabled(struct regulator_dev *rdev)
{
	int ret;
	struct ab8500_ext_regulator_info *info = rdev_get_drvdata(rdev);
	u8 regval;

	if (info == NULL) {
		dev_err(rdev_get_dev(rdev), "regulator info null pointer\n");
		return -EINVAL;
	}

	ret = abx500_get_register_interruptible(info->dev,
		info->update_bank, info->update_reg, &regval);
	if (ret < 0) {
		dev_err(rdev_get_dev(rdev),
			"couldn't read 0x%x register\n", info->update_reg);
		return ret;
	}

	dev_dbg(rdev_get_dev(rdev), "%s-is_enabled (bank, reg, mask, value):"
		" 0x%02x, 0x%02x, 0x%02x, 0x%02x\n",
		info->desc.name, info->update_bank, info->update_reg,
		info->update_mask, regval);

	if (((regval & info->update_mask) == info->update_val_lp) ||
	    ((regval & info->update_mask) == info->update_val_hp))
		return 1;
	else
		return 0;
}