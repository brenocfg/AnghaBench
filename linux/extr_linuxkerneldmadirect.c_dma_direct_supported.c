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
typedef  scalar_t__ u64 ;
struct device {scalar_t__ bus_dma_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 scalar_t__ __phys_to_dma (struct device*,int /*<<< orphan*/ ) ; 

int dma_direct_supported(struct device *dev, u64 mask)
{
#ifdef CONFIG_ZONE_DMA
	/*
	 * This check needs to be against the actual bit mask value, so
	 * use __phys_to_dma() here so that the SME encryption mask isn't
	 * part of the check.
	 */
	if (mask < __phys_to_dma(dev, DMA_BIT_MASK(ARCH_ZONE_DMA_BITS)))
		return 0;
#else
	/*
	 * Because 32-bit DMA masks are so common we expect every architecture
	 * to be able to satisfy them - either by not supporting more physical
	 * memory, or by providing a ZONE_DMA32.  If neither is the case, the
	 * architecture needs to use an IOMMU instead of the direct mapping.
	 *
	 * This check needs to be against the actual bit mask value, so
	 * use __phys_to_dma() here so that the SME encryption mask isn't
	 * part of the check.
	 */
	if (mask < __phys_to_dma(dev, DMA_BIT_MASK(32)))
		return 0;
#endif
	/*
	 * Upstream PCI/PCIe bridges or SoC interconnects may not carry
	 * as many DMA address bits as the device itself supports.
	 */
	if (dev->bus_dma_mask && mask > dev->bus_dma_mask)
		return 0;
	return 1;
}