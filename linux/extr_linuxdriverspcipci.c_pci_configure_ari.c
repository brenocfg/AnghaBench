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
typedef  int u32 ;
struct pci_dev {int ari_enabled; TYPE_1__* bus; scalar_t__ devfn; } ;
struct TYPE_2__ {struct pci_dev* self; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_EXP_DEVCAP2 ; 
 int PCI_EXP_DEVCAP2_ARI ; 
 int /*<<< orphan*/  PCI_EXP_DEVCTL2 ; 
 int /*<<< orphan*/  PCI_EXP_DEVCTL2_ARI ; 
 int /*<<< orphan*/  PCI_EXT_CAP_ID_ARI ; 
 scalar_t__ pci_find_ext_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_is_pcie (struct pci_dev*) ; 
 scalar_t__ pcie_ari_disabled ; 
 int /*<<< orphan*/  pcie_capability_clear_word (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcie_capability_read_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pcie_capability_set_word (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void pci_configure_ari(struct pci_dev *dev)
{
	u32 cap;
	struct pci_dev *bridge;

	if (pcie_ari_disabled || !pci_is_pcie(dev) || dev->devfn)
		return;

	bridge = dev->bus->self;
	if (!bridge)
		return;

	pcie_capability_read_dword(bridge, PCI_EXP_DEVCAP2, &cap);
	if (!(cap & PCI_EXP_DEVCAP2_ARI))
		return;

	if (pci_find_ext_capability(dev, PCI_EXT_CAP_ID_ARI)) {
		pcie_capability_set_word(bridge, PCI_EXP_DEVCTL2,
					 PCI_EXP_DEVCTL2_ARI);
		bridge->ari_enabled = 1;
	} else {
		pcie_capability_clear_word(bridge, PCI_EXP_DEVCTL2,
					   PCI_EXP_DEVCTL2_ARI);
		bridge->ari_enabled = 0;
	}
}