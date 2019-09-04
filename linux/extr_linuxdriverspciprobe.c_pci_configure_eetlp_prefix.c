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
struct pci_dev {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void pci_configure_eetlp_prefix(struct pci_dev *dev)
{
#ifdef CONFIG_PCI_PASID
	struct pci_dev *bridge;
	int pcie_type;
	u32 cap;

	if (!pci_is_pcie(dev))
		return;

	pcie_capability_read_dword(dev, PCI_EXP_DEVCAP2, &cap);
	if (!(cap & PCI_EXP_DEVCAP2_EE_PREFIX))
		return;

	pcie_type = pci_pcie_type(dev);
	if (pcie_type == PCI_EXP_TYPE_ROOT_PORT ||
	    pcie_type == PCI_EXP_TYPE_RC_END)
		dev->eetlp_prefix_path = 1;
	else {
		bridge = pci_upstream_bridge(dev);
		if (bridge && bridge->eetlp_prefix_path)
			dev->eetlp_prefix_path = 1;
	}
#endif
}