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
typedef  int u16 ;
struct pci_dev {int class; TYPE_1__* bus; } ;
struct TYPE_2__ {int bus_flags; } ;

/* Variables and functions */
 int PCI_BUS_FLAGS_NO_EXTCFG ; 
 int /*<<< orphan*/  PCI_CAP_ID_PCIX ; 
 int PCI_CFG_SPACE_SIZE ; 
 int PCI_CLASS_BRIDGE_HOST ; 
 scalar_t__ PCI_X_STATUS ; 
 int PCI_X_STATUS_266MHZ ; 
 int PCI_X_STATUS_533MHZ ; 
 int pci_cfg_space_size_ext (struct pci_dev*) ; 
 int pci_find_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_is_pcie (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,scalar_t__,int*) ; 

int pci_cfg_space_size(struct pci_dev *dev)
{
	int pos;
	u32 status;
	u16 class;

	if (dev->bus->bus_flags & PCI_BUS_FLAGS_NO_EXTCFG)
		return PCI_CFG_SPACE_SIZE;

	class = dev->class >> 8;
	if (class == PCI_CLASS_BRIDGE_HOST)
		return pci_cfg_space_size_ext(dev);

	if (pci_is_pcie(dev))
		return pci_cfg_space_size_ext(dev);

	pos = pci_find_capability(dev, PCI_CAP_ID_PCIX);
	if (!pos)
		return PCI_CFG_SPACE_SIZE;

	pci_read_config_dword(dev, pos + PCI_X_STATUS, &status);
	if (status & (PCI_X_STATUS_266MHZ | PCI_X_STATUS_533MHZ))
		return pci_cfg_space_size_ext(dev);

	return PCI_CFG_SPACE_SIZE;
}