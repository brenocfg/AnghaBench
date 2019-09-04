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
typedef  int u16 ;
struct pnv_php_slot {struct pci_dev* pdev; } ;
struct pci_dev {int dummy; } ;
struct msix_entry {int entry; int vector; } ;

/* Variables and functions */
 int ERANGE ; 
 int /*<<< orphan*/  PCI_EXP_FLAGS ; 
 int PCI_EXP_FLAGS_IRQ ; 
 int pci_enable_msix_exact (struct pci_dev*,struct msix_entry*,int) ; 
 int pci_msix_vec_count (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_warn (struct pci_dev*,char*,int) ; 
 int /*<<< orphan*/  pcie_capability_read_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int pnv_php_enable_msix(struct pnv_php_slot *php_slot)
{
	struct pci_dev *pdev = php_slot->pdev;
	struct msix_entry entry;
	int nr_entries, ret;
	u16 pcie_flag;

	/* Get total number of MSIx entries */
	nr_entries = pci_msix_vec_count(pdev);
	if (nr_entries < 0)
		return nr_entries;

	/* Check hotplug MSIx entry is in range */
	pcie_capability_read_word(pdev, PCI_EXP_FLAGS, &pcie_flag);
	entry.entry = (pcie_flag & PCI_EXP_FLAGS_IRQ) >> 9;
	if (entry.entry >= nr_entries)
		return -ERANGE;

	/* Enable MSIx */
	ret = pci_enable_msix_exact(pdev, &entry, 1);
	if (ret) {
		pci_warn(pdev, "Error %d enabling MSIx\n", ret);
		return ret;
	}

	return entry.vector;
}