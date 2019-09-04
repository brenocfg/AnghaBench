#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct tb_switch {int authorized; TYPE_1__ dev; int /*<<< orphan*/  tb; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int EINVAL ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  KOBJ_CHANGE ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_lock_rescan_remove () ; 
 int /*<<< orphan*/  pci_unlock_rescan_remove () ; 
 int /*<<< orphan*/  pm_runtime_get_sync (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (TYPE_1__*) ; 
 int /*<<< orphan*/  switch_lock ; 
 int tb_domain_approve_switch (int /*<<< orphan*/ ,struct tb_switch*) ; 
 int tb_domain_approve_switch_key (int /*<<< orphan*/ ,struct tb_switch*) ; 
 int tb_domain_challenge_switch_key (int /*<<< orphan*/ ,struct tb_switch*) ; 

__attribute__((used)) static int tb_switch_set_authorized(struct tb_switch *sw, unsigned int val)
{
	int ret = -EINVAL;

	if (mutex_lock_interruptible(&switch_lock))
		return -ERESTARTSYS;

	if (sw->authorized)
		goto unlock;

	/*
	 * Make sure there is no PCIe rescan ongoing when a new PCIe
	 * tunnel is created. Otherwise the PCIe rescan code might find
	 * the new tunnel too early.
	 */
	pci_lock_rescan_remove();
	pm_runtime_get_sync(&sw->dev);

	switch (val) {
	/* Approve switch */
	case 1:
		if (sw->key)
			ret = tb_domain_approve_switch_key(sw->tb, sw);
		else
			ret = tb_domain_approve_switch(sw->tb, sw);
		break;

	/* Challenge switch */
	case 2:
		if (sw->key)
			ret = tb_domain_challenge_switch_key(sw->tb, sw);
		break;

	default:
		break;
	}

	pm_runtime_mark_last_busy(&sw->dev);
	pm_runtime_put_autosuspend(&sw->dev);
	pci_unlock_rescan_remove();

	if (!ret) {
		sw->authorized = val;
		/* Notify status change to the userspace */
		kobject_uevent(&sw->dev.kobj, KOBJ_CHANGE);
	}

unlock:
	mutex_unlock(&switch_lock);
	return ret;
}