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

__attribute__((used)) static bool pci_ext_cfg_is_aliased(struct pci_dev *dev)
{
#ifdef CONFIG_PCI_QUIRKS
	int pos;
	u32 header, tmp;

	pci_read_config_dword(dev, PCI_VENDOR_ID, &header);

	for (pos = PCI_CFG_SPACE_SIZE;
	     pos < PCI_CFG_SPACE_EXP_SIZE; pos += PCI_CFG_SPACE_SIZE) {
		if (pci_read_config_dword(dev, pos, &tmp) != PCIBIOS_SUCCESSFUL
		    || header != tmp)
			return false;
	}

	return true;
#else
	return false;
#endif
}