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
typedef  int u16 ;
struct pci_dev {scalar_t__ msi_cap; int /*<<< orphan*/  irq; int /*<<< orphan*/  msi_enabled; } ;
struct TYPE_2__ {int multiple; int /*<<< orphan*/  multi_cap; } ;
struct msi_desc {TYPE_1__ msi_attrib; int /*<<< orphan*/  masked; } ;

/* Variables and functions */
 scalar_t__ PCI_MSI_FLAGS ; 
 int PCI_MSI_FLAGS_ENABLE ; 
 int PCI_MSI_FLAGS_QSIZE ; 
 int /*<<< orphan*/  arch_restore_msi_irqs (struct pci_dev*) ; 
 struct msi_desc* irq_get_msi_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_mask_irq (struct msi_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_intx_for_msi (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_msi_set_enable (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,scalar_t__,int*) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,scalar_t__,int) ; 

__attribute__((used)) static void __pci_restore_msi_state(struct pci_dev *dev)
{
	u16 control;
	struct msi_desc *entry;

	if (!dev->msi_enabled)
		return;

	entry = irq_get_msi_desc(dev->irq);

	pci_intx_for_msi(dev, 0);
	pci_msi_set_enable(dev, 0);
	arch_restore_msi_irqs(dev);

	pci_read_config_word(dev, dev->msi_cap + PCI_MSI_FLAGS, &control);
	msi_mask_irq(entry, msi_mask(entry->msi_attrib.multi_cap),
		     entry->masked);
	control &= ~PCI_MSI_FLAGS_QSIZE;
	control |= (entry->msi_attrib.multiple << 4) | PCI_MSI_FLAGS_ENABLE;
	pci_write_config_word(dev, dev->msi_cap + PCI_MSI_FLAGS, control);
}