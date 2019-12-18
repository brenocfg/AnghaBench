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
struct page {int dummy; } ;
struct device {int dummy; } ;
typedef  scalar_t__ phys_addr_t ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 unsigned long DMA_ATTR_SKIP_CPU_SYNC ; 
 int /*<<< orphan*/  DMA_MAPPING_ERROR ; 
 int /*<<< orphan*/  arch_sync_dma_for_device (struct device*,scalar_t__,size_t,int) ; 
 int /*<<< orphan*/  dev_is_dma_coherent (struct device*) ; 
 int /*<<< orphan*/  dma_direct_possible (struct device*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ page_to_phys (struct page*) ; 
 int /*<<< orphan*/  phys_to_dma (struct device*,scalar_t__) ; 
 int /*<<< orphan*/  report_addr (struct device*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  swiotlb_map (struct device*,scalar_t__*,int /*<<< orphan*/ *,size_t,int,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

dma_addr_t dma_direct_map_page(struct device *dev, struct page *page,
		unsigned long offset, size_t size, enum dma_data_direction dir,
		unsigned long attrs)
{
	phys_addr_t phys = page_to_phys(page) + offset;
	dma_addr_t dma_addr = phys_to_dma(dev, phys);

	if (unlikely(!dma_direct_possible(dev, dma_addr, size)) &&
	    !swiotlb_map(dev, &phys, &dma_addr, size, dir, attrs)) {
		report_addr(dev, dma_addr, size);
		return DMA_MAPPING_ERROR;
	}

	if (!dev_is_dma_coherent(dev) && !(attrs & DMA_ATTR_SKIP_CPU_SYNC))
		arch_sync_dma_for_device(dev, phys, size, dir);
	return dma_addr;
}