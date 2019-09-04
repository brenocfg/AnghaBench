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
struct tps6524x {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_WRITE_ENABLE ; 
 int __rmw_reg (struct tps6524x*,int,int,int) ; 
 int __write_reg (struct tps6524x*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rmw_protect(struct tps6524x *hw, int reg, int mask, int val)
{
	int ret;

	mutex_lock(&hw->lock);

	ret = __write_reg(hw, REG_WRITE_ENABLE, 1);
	if (ret) {
		dev_err(hw->dev, "failed to set write enable\n");
		goto error;
	}

	ret = __rmw_reg(hw, reg, mask, val);
	if (ret)
		dev_err(hw->dev, "failed to rmw register %d\n", reg);

	ret = __write_reg(hw, REG_WRITE_ENABLE, 0);
	if (ret) {
		dev_err(hw->dev, "failed to clear write enable\n");
		goto error;
	}

error:
	mutex_unlock(&hw->lock);

	return ret;
}