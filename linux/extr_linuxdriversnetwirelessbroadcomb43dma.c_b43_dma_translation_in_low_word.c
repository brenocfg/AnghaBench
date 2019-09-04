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
struct b43_wldev {int dummy; } ;
typedef  enum b43_dmatype { ____Placeholder_b43_dmatype } b43_dmatype ;

/* Variables and functions */
 int B43_DMA_64BIT ; 

__attribute__((used)) static bool b43_dma_translation_in_low_word(struct b43_wldev *dev,
					    enum b43_dmatype type)
{
	if (type != B43_DMA_64BIT)
		return true;

#ifdef CONFIG_B43_SSB
	if (dev->dev->bus_type == B43_BUS_SSB &&
	    dev->dev->sdev->bus->bustype == SSB_BUSTYPE_PCI &&
	    !(pci_is_pcie(dev->dev->sdev->bus->host_pci) &&
	      ssb_read32(dev->dev->sdev, SSB_TMSHIGH) & SSB_TMSHIGH_DMA64))
			return true;
#endif
	return false;
}