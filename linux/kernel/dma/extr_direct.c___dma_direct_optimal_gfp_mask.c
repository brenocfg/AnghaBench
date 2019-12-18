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
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ARCH_ZONE_DMA_BITS ; 
 scalar_t__ DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  GFP_DMA ; 
 int /*<<< orphan*/  GFP_DMA32 ; 
 scalar_t__ __dma_to_phys (struct device*,scalar_t__) ; 
 scalar_t__ dma_to_phys (struct device*,scalar_t__) ; 
 scalar_t__ force_dma_unencrypted (struct device*) ; 

__attribute__((used)) static gfp_t __dma_direct_optimal_gfp_mask(struct device *dev, u64 dma_mask,
		u64 *phys_mask)
{
	if (dev->bus_dma_mask && dev->bus_dma_mask < dma_mask)
		dma_mask = dev->bus_dma_mask;

	if (force_dma_unencrypted(dev))
		*phys_mask = __dma_to_phys(dev, dma_mask);
	else
		*phys_mask = dma_to_phys(dev, dma_mask);

	/*
	 * Optimistically try the zone that the physical address mask falls
	 * into first.  If that returns memory that isn't actually addressable
	 * we will fallback to the next lower zone and try again.
	 *
	 * Note that GFP_DMA32 and GFP_DMA are no ops without the corresponding
	 * zones.
	 */
	if (*phys_mask <= DMA_BIT_MASK(ARCH_ZONE_DMA_BITS))
		return GFP_DMA;
	if (*phys_mask <= DMA_BIT_MASK(32))
		return GFP_DMA32;
	return 0;
}