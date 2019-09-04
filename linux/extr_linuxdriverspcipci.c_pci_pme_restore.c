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
struct pci_dev {scalar_t__ pm_cap; scalar_t__ wakeup_prepared; int /*<<< orphan*/  pme_support; } ;

/* Variables and functions */
 scalar_t__ PCI_PM_CTRL ; 
 int /*<<< orphan*/  PCI_PM_CTRL_PME_ENABLE ; 
 int /*<<< orphan*/  PCI_PM_CTRL_PME_STATUS ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,scalar_t__,int /*<<< orphan*/ ) ; 

void pci_pme_restore(struct pci_dev *dev)
{
	u16 pmcsr;

	if (!dev->pme_support)
		return;

	pci_read_config_word(dev, dev->pm_cap + PCI_PM_CTRL, &pmcsr);
	if (dev->wakeup_prepared) {
		pmcsr |= PCI_PM_CTRL_PME_ENABLE;
		pmcsr &= ~PCI_PM_CTRL_PME_STATUS;
	} else {
		pmcsr &= ~PCI_PM_CTRL_PME_ENABLE;
		pmcsr |= PCI_PM_CTRL_PME_STATUS;
	}
	pci_write_config_word(dev, dev->pm_cap + PCI_PM_CTRL, pmcsr);
}