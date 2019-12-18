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
struct dma_map_ops {int /*<<< orphan*/ * mmap; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_ARCH_HAS_DMA_COHERENT_TO_PFN ; 
 int /*<<< orphan*/  CONFIG_MMU ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ dev_is_dma_coherent (struct device*) ; 
 scalar_t__ dma_is_direct (struct dma_map_ops const*) ; 
 struct dma_map_ops* get_dma_ops (struct device*) ; 

bool dma_can_mmap(struct device *dev)
{
	const struct dma_map_ops *ops = get_dma_ops(dev);

	if (dma_is_direct(ops)) {
		return IS_ENABLED(CONFIG_MMU) &&
		       (dev_is_dma_coherent(dev) ||
			IS_ENABLED(CONFIG_ARCH_HAS_DMA_COHERENT_TO_PFN));
	}

	return ops->mmap != NULL;
}