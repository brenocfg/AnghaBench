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
typedef  int u32 ;
struct pci_dev {int dummy; } ;
typedef  enum pcie_link_width { ____Placeholder_pcie_link_width } pcie_link_width ;
typedef  enum pci_bus_speed { ____Placeholder_pci_bus_speed } pci_bus_speed ;

/* Variables and functions */
 int PCIE_LNK_WIDTH_UNKNOWN ; 
 int PCIE_SPEED2MBS_ENC (int) ; 
 int PCI_SPEED_UNKNOWN ; 
 int pcie_get_speed_cap (struct pci_dev*) ; 
 int pcie_get_width_cap (struct pci_dev*) ; 

u32 pcie_bandwidth_capable(struct pci_dev *dev, enum pci_bus_speed *speed,
			   enum pcie_link_width *width)
{
	*speed = pcie_get_speed_cap(dev);
	*width = pcie_get_width_cap(dev);

	if (*speed == PCI_SPEED_UNKNOWN || *width == PCIE_LNK_WIDTH_UNKNOWN)
		return 0;

	return *width * PCIE_SPEED2MBS_ENC(*speed);
}