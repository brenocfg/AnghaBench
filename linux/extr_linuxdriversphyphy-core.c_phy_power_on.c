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
struct phy {scalar_t__ power_count; scalar_t__ pwr; int /*<<< orphan*/  mutex; int /*<<< orphan*/  dev; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* power_on ) (struct phy*) ;} ;

/* Variables and functions */
 int ENOTSUPP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int phy_pm_runtime_get_sync (struct phy*) ; 
 int /*<<< orphan*/  phy_pm_runtime_put_sync (struct phy*) ; 
 int /*<<< orphan*/  regulator_disable (scalar_t__) ; 
 int regulator_enable (scalar_t__) ; 
 int stub1 (struct phy*) ; 

int phy_power_on(struct phy *phy)
{
	int ret = 0;

	if (!phy)
		goto out;

	if (phy->pwr) {
		ret = regulator_enable(phy->pwr);
		if (ret)
			goto out;
	}

	ret = phy_pm_runtime_get_sync(phy);
	if (ret < 0 && ret != -ENOTSUPP)
		goto err_pm_sync;

	ret = 0; /* Override possible ret == -ENOTSUPP */

	mutex_lock(&phy->mutex);
	if (phy->power_count == 0 && phy->ops->power_on) {
		ret = phy->ops->power_on(phy);
		if (ret < 0) {
			dev_err(&phy->dev, "phy poweron failed --> %d\n", ret);
			goto err_pwr_on;
		}
	}
	++phy->power_count;
	mutex_unlock(&phy->mutex);
	return 0;

err_pwr_on:
	mutex_unlock(&phy->mutex);
	phy_pm_runtime_put_sync(phy);
err_pm_sync:
	if (phy->pwr)
		regulator_disable(phy->pwr);
out:
	return ret;
}