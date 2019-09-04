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
typedef  size_t u16 ;
struct pci_dev {int dummy; } ;
typedef  enum pcie_link_width { ____Placeholder_pcie_link_width } pcie_link_width ;
typedef  enum pci_bus_speed { ____Placeholder_pci_bus_speed } pci_bus_speed ;

/* Variables and functions */
 int PCIE_LNK_WIDTH_UNKNOWN ; 
 int PCIE_SPEED2MBS_ENC (int) ; 
 int /*<<< orphan*/  PCI_EXP_LNKSTA ; 
 size_t PCI_EXP_LNKSTA_CLS ; 
 size_t PCI_EXP_LNKSTA_NLW ; 
 size_t PCI_EXP_LNKSTA_NLW_SHIFT ; 
 int PCI_SPEED_UNKNOWN ; 
 struct pci_dev* pci_upstream_bridge (struct pci_dev*) ; 
 int /*<<< orphan*/  pcie_capability_read_word (struct pci_dev*,int /*<<< orphan*/ ,size_t*) ; 
 int* pcie_link_speed ; 

u32 pcie_bandwidth_available(struct pci_dev *dev, struct pci_dev **limiting_dev,
			     enum pci_bus_speed *speed,
			     enum pcie_link_width *width)
{
	u16 lnksta;
	enum pci_bus_speed next_speed;
	enum pcie_link_width next_width;
	u32 bw, next_bw;

	if (speed)
		*speed = PCI_SPEED_UNKNOWN;
	if (width)
		*width = PCIE_LNK_WIDTH_UNKNOWN;

	bw = 0;

	while (dev) {
		pcie_capability_read_word(dev, PCI_EXP_LNKSTA, &lnksta);

		next_speed = pcie_link_speed[lnksta & PCI_EXP_LNKSTA_CLS];
		next_width = (lnksta & PCI_EXP_LNKSTA_NLW) >>
			PCI_EXP_LNKSTA_NLW_SHIFT;

		next_bw = next_width * PCIE_SPEED2MBS_ENC(next_speed);

		/* Check if current device limits the total bandwidth */
		if (!bw || next_bw <= bw) {
			bw = next_bw;

			if (limiting_dev)
				*limiting_dev = dev;
			if (speed)
				*speed = next_speed;
			if (width)
				*width = next_width;
		}

		dev = pci_upstream_bridge(dev);
	}

	return bw;
}