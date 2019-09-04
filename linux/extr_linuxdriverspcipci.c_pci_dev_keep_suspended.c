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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct device {TYPE_1__ power; } ;
struct pci_dev {scalar_t__ current_state; struct device dev; } ;

/* Variables and functions */
 scalar_t__ PCI_D3cold ; 
 int /*<<< orphan*/  __pci_pme_active (struct pci_dev*,int) ; 
 int device_may_wakeup (struct device*) ; 
 scalar_t__ pci_target_state (struct pci_dev*,int) ; 
 scalar_t__ platform_pci_need_resume (struct pci_dev*) ; 
 scalar_t__ pm_runtime_suspended (struct device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

bool pci_dev_keep_suspended(struct pci_dev *pci_dev)
{
	struct device *dev = &pci_dev->dev;
	bool wakeup = device_may_wakeup(dev);

	if (!pm_runtime_suspended(dev)
	    || pci_target_state(pci_dev, wakeup) != pci_dev->current_state
	    || platform_pci_need_resume(pci_dev))
		return false;

	/*
	 * At this point the device is good to go unless it's been configured
	 * to generate PME at the runtime suspend time, but it is not supposed
	 * to wake up the system.  In that case, simply disable PME for it
	 * (it will have to be re-enabled on exit from system resume).
	 *
	 * If the device's power state is D3cold and the platform check above
	 * hasn't triggered, the device's configuration is suitable and we don't
	 * need to manipulate it at all.
	 */
	spin_lock_irq(&dev->power.lock);

	if (pm_runtime_suspended(dev) && pci_dev->current_state < PCI_D3cold &&
	    !wakeup)
		__pci_pme_active(pci_dev, false);

	spin_unlock_irq(&dev->power.lock);
	return true;
}