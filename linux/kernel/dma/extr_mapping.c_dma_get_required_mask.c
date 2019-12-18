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
typedef  int /*<<< orphan*/  u64 ;
struct dma_map_ops {int /*<<< orphan*/  (* get_required_mask ) (struct device*) ;} ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  dma_direct_get_required_mask (struct device*) ; 
 scalar_t__ dma_is_direct (struct dma_map_ops const*) ; 
 struct dma_map_ops* get_dma_ops (struct device*) ; 
 int /*<<< orphan*/  stub1 (struct device*) ; 

u64 dma_get_required_mask(struct device *dev)
{
	const struct dma_map_ops *ops = get_dma_ops(dev);

	if (dma_is_direct(ops))
		return dma_direct_get_required_mask(dev);
	if (ops->get_required_mask)
		return ops->get_required_mask(dev);

	/*
	 * We require every DMA ops implementation to at least support a 32-bit
	 * DMA mask (and use bounce buffering if that isn't supported in
	 * hardware).  As the direct mapping code has its own routine to
	 * actually report an optimal mask we default to 32-bit here as that
	 * is the right thing for most IOMMUs, and at least not actively
	 * harmful in general.
	 */
	return DMA_BIT_MASK(32);
}