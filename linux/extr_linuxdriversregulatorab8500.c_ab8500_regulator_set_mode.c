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
typedef  scalar_t__ u8 ;
struct regulator_dev {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct ab8500_regulator_info {TYPE_2__* shared_mode; scalar_t__ update_val; scalar_t__ mode_mask; TYPE_1__ desc; int /*<<< orphan*/  dev; scalar_t__ update_val_idle; scalar_t__ mode_val_idle; scalar_t__ update_val_normal; scalar_t__ mode_val_normal; scalar_t__ update_mask; scalar_t__ update_reg; scalar_t__ update_bank; scalar_t__ mode_reg; scalar_t__ mode_bank; } ;
struct TYPE_4__ {int lp_mode_req; struct ab8500_regulator_info* shared_regulator; } ;

/* Variables and functions */
 int EINVAL ; 
#define  REGULATOR_MODE_IDLE 129 
#define  REGULATOR_MODE_NORMAL 128 
 scalar_t__ ab8500_regulator_is_enabled (struct regulator_dev*) ; 
 int abx500_mask_and_set_register_interruptible (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdev_get_dev (struct regulator_dev*) ; 
 struct ab8500_regulator_info* rdev_get_drvdata (struct regulator_dev*) ; 
 int /*<<< orphan*/  shared_mode_mutex ; 

__attribute__((used)) static int ab8500_regulator_set_mode(struct regulator_dev *rdev,
				     unsigned int mode)
{
	int ret = 0;
	u8 bank, reg, mask, val;
	bool lp_mode_req = false;
	struct ab8500_regulator_info *info = rdev_get_drvdata(rdev);

	if (info == NULL) {
		dev_err(rdev_get_dev(rdev), "regulator info null pointer\n");
		return -EINVAL;
	}

	if (info->mode_mask) {
		bank = info->mode_bank;
		reg = info->mode_reg;
		mask = info->mode_mask;
	} else {
		bank = info->update_bank;
		reg = info->update_reg;
		mask = info->update_mask;
	}

	if (info->shared_mode)
		mutex_lock(&shared_mode_mutex);

	switch (mode) {
	case REGULATOR_MODE_NORMAL:
		if (info->shared_mode)
			lp_mode_req = false;

		if (info->mode_mask)
			val = info->mode_val_normal;
		else
			val = info->update_val_normal;
		break;
	case REGULATOR_MODE_IDLE:
		if (info->shared_mode) {
			struct ab8500_regulator_info *shared_regulator;

			shared_regulator = info->shared_mode->shared_regulator;
			if (!shared_regulator->shared_mode->lp_mode_req) {
				/* Other regulator prevent LP mode */
				info->shared_mode->lp_mode_req = true;
				goto out_unlock;
			}

			lp_mode_req = true;
		}

		if (info->mode_mask)
			val = info->mode_val_idle;
		else
			val = info->update_val_idle;
		break;
	default:
		ret = -EINVAL;
		goto out_unlock;
	}

	if (info->mode_mask || ab8500_regulator_is_enabled(rdev)) {
		ret = abx500_mask_and_set_register_interruptible(info->dev,
			bank, reg, mask, val);
		if (ret < 0) {
			dev_err(rdev_get_dev(rdev),
				"couldn't set regulator mode\n");
			goto out_unlock;
		}

		dev_vdbg(rdev_get_dev(rdev),
			"%s-set_mode (bank, reg, mask, value): "
			"0x%x, 0x%x, 0x%x, 0x%x\n",
			info->desc.name, bank, reg,
			mask, val);
	}

	if (!info->mode_mask)
		info->update_val = val;

	if (info->shared_mode)
		info->shared_mode->lp_mode_req = lp_mode_req;

out_unlock:
	if (info->shared_mode)
		mutex_unlock(&shared_mode_mutex);

	return ret;
}