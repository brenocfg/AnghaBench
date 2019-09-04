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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct pnv_php_slot {int flags; int irq; int /*<<< orphan*/  name; int /*<<< orphan*/  dn; int /*<<< orphan*/  wq; struct pci_dev* pdev; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  PCI_EXP_SLTCTL ; 
 int PCI_EXP_SLTCTL_DLLSCE ; 
 int PCI_EXP_SLTCTL_HPIE ; 
 int PCI_EXP_SLTCTL_PDCE ; 
 int /*<<< orphan*/  PCI_EXP_SLTSTA ; 
 int PCI_EXP_SLTSTA_DLLSC ; 
 int PCI_EXP_SLTSTA_PDC ; 
 int PNV_PHP_FLAG_BROKEN_PDC ; 
 int /*<<< orphan*/  alloc_workqueue (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int of_property_read_u32 (int /*<<< orphan*/ ,char*,scalar_t__*) ; 
 int /*<<< orphan*/  pci_warn (struct pci_dev*,char*,...) ; 
 int /*<<< orphan*/  pcie_capability_read_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pcie_capability_write_word (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pnv_php_disable_irq (struct pnv_php_slot*,int) ; 
 int /*<<< orphan*/  pnv_php_interrupt ; 
 int request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pnv_php_slot*) ; 

__attribute__((used)) static void pnv_php_init_irq(struct pnv_php_slot *php_slot, int irq)
{
	struct pci_dev *pdev = php_slot->pdev;
	u32 broken_pdc = 0;
	u16 sts, ctrl;
	int ret;

	/* Allocate workqueue */
	php_slot->wq = alloc_workqueue("pciehp-%s", 0, 0, php_slot->name);
	if (!php_slot->wq) {
		pci_warn(pdev, "Cannot alloc workqueue\n");
		pnv_php_disable_irq(php_slot, true);
		return;
	}

	/* Check PDC (Presence Detection Change) is broken or not */
	ret = of_property_read_u32(php_slot->dn, "ibm,slot-broken-pdc",
				   &broken_pdc);
	if (!ret && broken_pdc)
		php_slot->flags |= PNV_PHP_FLAG_BROKEN_PDC;

	/* Clear pending interrupts */
	pcie_capability_read_word(pdev, PCI_EXP_SLTSTA, &sts);
	if (php_slot->flags & PNV_PHP_FLAG_BROKEN_PDC)
		sts |= PCI_EXP_SLTSTA_DLLSC;
	else
		sts |= (PCI_EXP_SLTSTA_PDC | PCI_EXP_SLTSTA_DLLSC);
	pcie_capability_write_word(pdev, PCI_EXP_SLTSTA, sts);

	/* Request the interrupt */
	ret = request_irq(irq, pnv_php_interrupt, IRQF_SHARED,
			  php_slot->name, php_slot);
	if (ret) {
		pnv_php_disable_irq(php_slot, true);
		pci_warn(pdev, "Error %d enabling IRQ %d\n", ret, irq);
		return;
	}

	/* Enable the interrupts */
	pcie_capability_read_word(pdev, PCI_EXP_SLTCTL, &ctrl);
	if (php_slot->flags & PNV_PHP_FLAG_BROKEN_PDC) {
		ctrl &= ~PCI_EXP_SLTCTL_PDCE;
		ctrl |= (PCI_EXP_SLTCTL_HPIE |
			 PCI_EXP_SLTCTL_DLLSCE);
	} else {
		ctrl |= (PCI_EXP_SLTCTL_HPIE |
			 PCI_EXP_SLTCTL_PDCE |
			 PCI_EXP_SLTCTL_DLLSCE);
	}
	pcie_capability_write_word(pdev, PCI_EXP_SLTCTL, ctrl);

	/* The interrupt is initialized successfully when @irq is valid */
	php_slot->irq = irq;
}