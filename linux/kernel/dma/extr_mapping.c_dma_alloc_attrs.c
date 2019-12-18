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
struct dma_map_ops {void* (* alloc ) (struct device*,size_t,int /*<<< orphan*/ *,int,unsigned long) ;} ;
struct device {int /*<<< orphan*/  coherent_dma_mask; } ;
typedef  int gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int __GFP_DMA ; 
 int __GFP_DMA32 ; 
 int __GFP_HIGHMEM ; 
 int /*<<< orphan*/  debug_dma_alloc_coherent (struct device*,size_t,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ dma_alloc_from_dev_coherent (struct device*,size_t,int /*<<< orphan*/ *,void**) ; 
 void* dma_direct_alloc (struct device*,size_t,int /*<<< orphan*/ *,int,unsigned long) ; 
 scalar_t__ dma_is_direct (struct dma_map_ops const*) ; 
 struct dma_map_ops* get_dma_ops (struct device*) ; 
 void* stub1 (struct device*,size_t,int /*<<< orphan*/ *,int,unsigned long) ; 

void *dma_alloc_attrs(struct device *dev, size_t size, dma_addr_t *dma_handle,
		gfp_t flag, unsigned long attrs)
{
	const struct dma_map_ops *ops = get_dma_ops(dev);
	void *cpu_addr;

	WARN_ON_ONCE(!dev->coherent_dma_mask);

	if (dma_alloc_from_dev_coherent(dev, size, dma_handle, &cpu_addr))
		return cpu_addr;

	/* let the implementation decide on the zone to allocate from: */
	flag &= ~(__GFP_DMA | __GFP_DMA32 | __GFP_HIGHMEM);

	if (dma_is_direct(ops))
		cpu_addr = dma_direct_alloc(dev, size, dma_handle, flag, attrs);
	else if (ops->alloc)
		cpu_addr = ops->alloc(dev, size, dma_handle, flag, attrs);
	else
		return NULL;

	debug_dma_alloc_coherent(dev, size, *dma_handle, cpu_addr);
	return cpu_addr;
}