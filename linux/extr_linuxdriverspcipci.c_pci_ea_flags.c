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
typedef  int u8 ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 unsigned long IORESOURCE_IO ; 
 unsigned long IORESOURCE_MEM ; 
 unsigned long IORESOURCE_PCI_EA_BEI ; 
 unsigned long IORESOURCE_PCI_FIXED ; 
 unsigned long IORESOURCE_PREFETCH ; 
#define  PCI_EA_P_IO 132 
#define  PCI_EA_P_MEM 131 
#define  PCI_EA_P_MEM_PREFETCH 130 
#define  PCI_EA_P_VF_MEM 129 
#define  PCI_EA_P_VF_MEM_PREFETCH 128 

__attribute__((used)) static unsigned long pci_ea_flags(struct pci_dev *dev, u8 prop)
{
	unsigned long flags = IORESOURCE_PCI_FIXED | IORESOURCE_PCI_EA_BEI;

	switch (prop) {
	case PCI_EA_P_MEM:
	case PCI_EA_P_VF_MEM:
		flags |= IORESOURCE_MEM;
		break;
	case PCI_EA_P_MEM_PREFETCH:
	case PCI_EA_P_VF_MEM_PREFETCH:
		flags |= IORESOURCE_MEM | IORESOURCE_PREFETCH;
		break;
	case PCI_EA_P_IO:
		flags |= IORESOURCE_IO;
		break;
	default:
		return 0;
	}

	return flags;
}