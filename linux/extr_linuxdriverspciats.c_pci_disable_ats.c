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
struct pci_dev {scalar_t__ ats_enabled; scalar_t__ ats_cap; int /*<<< orphan*/  ats_ref_cnt; scalar_t__ is_virtfn; } ;

/* Variables and functions */
 scalar_t__ PCI_ATS_CTRL ; 
 int /*<<< orphan*/  PCI_ATS_CTRL_ENABLE ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 struct pci_dev* pci_physfn (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,scalar_t__,int /*<<< orphan*/ ) ; 

void pci_disable_ats(struct pci_dev *dev)
{
	struct pci_dev *pdev;
	u16 ctrl;

	if (WARN_ON(!dev->ats_enabled))
		return;

	if (atomic_read(&dev->ats_ref_cnt))
		return;		/* VFs still enabled */

	if (dev->is_virtfn) {
		pdev = pci_physfn(dev);
		atomic_dec(&pdev->ats_ref_cnt);
	}

	pci_read_config_word(dev, dev->ats_cap + PCI_ATS_CTRL, &ctrl);
	ctrl &= ~PCI_ATS_CTRL_ENABLE;
	pci_write_config_word(dev, dev->ats_cap + PCI_ATS_CTRL, ctrl);

	dev->ats_enabled = 0;
}