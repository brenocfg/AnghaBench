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
typedef  scalar_t__ u8 ;
struct resource {int dummy; } ;
struct pci_dev {struct resource* resource; } ;

/* Variables and functions */
 scalar_t__ PCI_EA_BEI_BAR5 ; 
 scalar_t__ PCI_EA_BEI_ROM ; 
 scalar_t__ PCI_EA_P_IO ; 
 size_t PCI_ROM_RESOURCE ; 

__attribute__((used)) static struct resource *pci_ea_get_resource(struct pci_dev *dev, u8 bei,
					    u8 prop)
{
	if (bei <= PCI_EA_BEI_BAR5 && prop <= PCI_EA_P_IO)
		return &dev->resource[bei];
#ifdef CONFIG_PCI_IOV
	else if (bei >= PCI_EA_BEI_VF_BAR0 && bei <= PCI_EA_BEI_VF_BAR5 &&
		 (prop == PCI_EA_P_VF_MEM || prop == PCI_EA_P_VF_MEM_PREFETCH))
		return &dev->resource[PCI_IOV_RESOURCES +
				      bei - PCI_EA_BEI_VF_BAR0];
#endif
	else if (bei == PCI_EA_BEI_ROM)
		return &dev->resource[PCI_ROM_RESOURCE];
	else
		return NULL;
}