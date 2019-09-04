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
 int /*<<< orphan*/  pci_dev_run_wake (struct pci_dev*) ; 
 scalar_t__ pm_runtime_suspended (struct device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void pci_dev_complete_resume(struct pci_dev *pci_dev)
{
	struct device *dev = &pci_dev->dev;

	if (!pci_dev_run_wake(pci_dev))
		return;

	spin_lock_irq(&dev->power.lock);

	if (pm_runtime_suspended(dev) && pci_dev->current_state < PCI_D3cold)
		__pci_pme_active(pci_dev, true);

	spin_unlock_irq(&dev->power.lock);
}