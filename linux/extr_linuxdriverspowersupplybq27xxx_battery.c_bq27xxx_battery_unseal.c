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
typedef  int /*<<< orphan*/  u16 ;
struct bq27xxx_device_info {int unseal_key; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BQ27XXX_REG_CTRL ; 
 int EINVAL ; 
 int bq27xxx_write (struct bq27xxx_device_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int bq27xxx_battery_unseal(struct bq27xxx_device_info *di)
{
	int ret;

	if (di->unseal_key == 0) {
		dev_err(di->dev, "unseal failed due to missing key\n");
		return -EINVAL;
	}

	ret = bq27xxx_write(di, BQ27XXX_REG_CTRL, (u16)(di->unseal_key >> 16), false);
	if (ret < 0)
		goto out;

	ret = bq27xxx_write(di, BQ27XXX_REG_CTRL, (u16)di->unseal_key, false);
	if (ret < 0)
		goto out;

	return 0;

out:
	dev_err(di->dev, "bus error on unseal: %d\n", ret);
	return ret;
}