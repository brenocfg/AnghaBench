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
struct phy {int power_count; scalar_t__ pwr; int /*<<< orphan*/  mutex; int /*<<< orphan*/  dev; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* power_off ) (struct phy*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phy_pm_runtime_put (struct phy*) ; 
 int /*<<< orphan*/  regulator_disable (scalar_t__) ; 
 int stub1 (struct phy*) ; 

int phy_power_off(struct phy *phy)
{
	int ret;

	if (!phy)
		return 0;

	mutex_lock(&phy->mutex);
	if (phy->power_count == 1 && phy->ops->power_off) {
		ret =  phy->ops->power_off(phy);
		if (ret < 0) {
			dev_err(&phy->dev, "phy poweroff failed --> %d\n", ret);
			mutex_unlock(&phy->mutex);
			return ret;
		}
	}
	--phy->power_count;
	mutex_unlock(&phy->mutex);
	phy_pm_runtime_put(phy);

	if (phy->pwr)
		regulator_disable(phy->pwr);

	return 0;
}