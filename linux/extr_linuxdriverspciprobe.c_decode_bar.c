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

/* Variables and functions */
 unsigned long IORESOURCE_IO ; 
 unsigned long IORESOURCE_MEM ; 
 unsigned long IORESOURCE_MEM_64 ; 
 unsigned long IORESOURCE_PREFETCH ; 
 int PCI_BASE_ADDRESS_IO_MASK ; 
 int PCI_BASE_ADDRESS_MEM_MASK ; 
 unsigned long PCI_BASE_ADDRESS_MEM_PREFETCH ; 
#define  PCI_BASE_ADDRESS_MEM_TYPE_1M 130 
#define  PCI_BASE_ADDRESS_MEM_TYPE_32 129 
#define  PCI_BASE_ADDRESS_MEM_TYPE_64 128 
 int PCI_BASE_ADDRESS_MEM_TYPE_MASK ; 
 int PCI_BASE_ADDRESS_SPACE ; 
 int PCI_BASE_ADDRESS_SPACE_IO ; 

__attribute__((used)) static inline unsigned long decode_bar(struct pci_dev *dev, u32 bar)
{
	u32 mem_type;
	unsigned long flags;

	if ((bar & PCI_BASE_ADDRESS_SPACE) == PCI_BASE_ADDRESS_SPACE_IO) {
		flags = bar & ~PCI_BASE_ADDRESS_IO_MASK;
		flags |= IORESOURCE_IO;
		return flags;
	}

	flags = bar & ~PCI_BASE_ADDRESS_MEM_MASK;
	flags |= IORESOURCE_MEM;
	if (flags & PCI_BASE_ADDRESS_MEM_PREFETCH)
		flags |= IORESOURCE_PREFETCH;

	mem_type = bar & PCI_BASE_ADDRESS_MEM_TYPE_MASK;
	switch (mem_type) {
	case PCI_BASE_ADDRESS_MEM_TYPE_32:
		break;
	case PCI_BASE_ADDRESS_MEM_TYPE_1M:
		/* 1M mem BAR treated as 32-bit BAR */
		break;
	case PCI_BASE_ADDRESS_MEM_TYPE_64:
		flags |= IORESOURCE_MEM_64;
		break;
	default:
		/* mem unknown type treated as 32-bit BAR */
		break;
	}
	return flags;
}