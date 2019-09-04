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
typedef  int /*<<< orphan*/  u32 ;
struct ssb_device {TYPE_1__* bus; } ;
struct TYPE_2__ {int bustype; int /*<<< orphan*/  host_pci; } ;

/* Variables and functions */
#define  SSB_BUSTYPE_PCI 129 
#define  SSB_BUSTYPE_SSB 128 
 int /*<<< orphan*/  SSB_PCIE_DMA_H32 ; 
 int /*<<< orphan*/  SSB_PCI_DMA ; 
 int /*<<< orphan*/  SSB_TMSHIGH ; 
 int SSB_TMSHIGH_DMA64 ; 
 int /*<<< orphan*/  __ssb_dma_not_implemented (struct ssb_device*) ; 
 int /*<<< orphan*/  pci_is_pcie (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssb_dma_translation_special_bit (struct ssb_device*) ; 
 int ssb_read32 (struct ssb_device*,int /*<<< orphan*/ ) ; 

u32 ssb_dma_translation(struct ssb_device *dev)
{
	switch (dev->bus->bustype) {
	case SSB_BUSTYPE_SSB:
		return 0;
	case SSB_BUSTYPE_PCI:
		if (pci_is_pcie(dev->bus->host_pci) &&
		    ssb_read32(dev, SSB_TMSHIGH) & SSB_TMSHIGH_DMA64) {
			return SSB_PCIE_DMA_H32;
		} else {
			if (ssb_dma_translation_special_bit(dev))
				return SSB_PCIE_DMA_H32;
			else
				return SSB_PCI_DMA;
		}
	default:
		__ssb_dma_not_implemented(dev);
	}
	return 0;
}