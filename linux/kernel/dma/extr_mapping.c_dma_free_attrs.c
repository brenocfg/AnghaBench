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
struct dma_map_ops {int /*<<< orphan*/  (* free ) (struct device*,size_t,void*,int /*<<< orphan*/ ,unsigned long) ;} ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_dma_free_coherent (struct device*,size_t,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_direct_free (struct device*,size_t,void*,int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ dma_is_direct (struct dma_map_ops const*) ; 
 scalar_t__ dma_release_from_dev_coherent (struct device*,int /*<<< orphan*/ ,void*) ; 
 struct dma_map_ops* get_dma_ops (struct device*) ; 
 int /*<<< orphan*/  get_order (size_t) ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 int /*<<< orphan*/  stub1 (struct device*,size_t,void*,int /*<<< orphan*/ ,unsigned long) ; 

void dma_free_attrs(struct device *dev, size_t size, void *cpu_addr,
		dma_addr_t dma_handle, unsigned long attrs)
{
	const struct dma_map_ops *ops = get_dma_ops(dev);

	if (dma_release_from_dev_coherent(dev, get_order(size), cpu_addr))
		return;
	/*
	 * On non-coherent platforms which implement DMA-coherent buffers via
	 * non-cacheable remaps, ops->free() may call vunmap(). Thus getting
	 * this far in IRQ context is a) at risk of a BUG_ON() or trying to
	 * sleep on some machines, and b) an indication that the driver is
	 * probably misusing the coherent API anyway.
	 */
	WARN_ON(irqs_disabled());

	if (!cpu_addr)
		return;

	debug_dma_free_coherent(dev, size, cpu_addr, dma_handle);
	if (dma_is_direct(ops))
		dma_direct_free(dev, size, cpu_addr, dma_handle, attrs);
	else if (ops->free)
		ops->free(dev, size, cpu_addr, dma_handle, attrs);
}