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
struct cstate {int id; } ;

/* Variables and functions */
#define  NBP1 131 
#define  NON_PC0 130 
#define  PC1 129 
#define  PC6 128 
 unsigned int PCI_NBP1_ENTERED_BIT ; 
 unsigned int PCI_NBP1_STAT_OFFSET ; 
 unsigned int PCI_NON_PC0_ENABLE_BIT ; 
 unsigned int PCI_NON_PC0_OFFSET ; 
 unsigned int PCI_PC1_ENABLE_BIT ; 
 unsigned int PCI_PC1_OFFSET ; 
 unsigned int PCI_PC6_ENABLE_BIT ; 
 unsigned int PCI_PC6_OFFSET ; 

__attribute__((used)) static int amd_fam14h_get_pci_info(struct cstate *state,
				   unsigned int *pci_offset,
				   unsigned int *enable_bit,
				   unsigned int cpu)
{
	switch (state->id) {
	case NON_PC0:
		*enable_bit = PCI_NON_PC0_ENABLE_BIT;
		*pci_offset = PCI_NON_PC0_OFFSET;
		break;
	case PC1:
		*enable_bit = PCI_PC1_ENABLE_BIT;
		*pci_offset = PCI_PC1_OFFSET;
		break;
	case PC6:
		*enable_bit = PCI_PC6_ENABLE_BIT;
		*pci_offset = PCI_PC6_OFFSET;
		break;
	case NBP1:
		*enable_bit = PCI_NBP1_ENTERED_BIT;
		*pci_offset = PCI_NBP1_STAT_OFFSET;
		break;
	default:
		return -1;
	};
	return 0;
}