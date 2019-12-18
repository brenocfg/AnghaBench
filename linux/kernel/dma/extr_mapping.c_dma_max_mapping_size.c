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
struct dma_map_ops {size_t (* max_mapping_size ) (struct device*) ;} ;
struct device {int dummy; } ;

/* Variables and functions */
 size_t SIZE_MAX ; 
 size_t dma_direct_max_mapping_size (struct device*) ; 
 scalar_t__ dma_is_direct (struct dma_map_ops const*) ; 
 struct dma_map_ops* get_dma_ops (struct device*) ; 
 size_t stub1 (struct device*) ; 

size_t dma_max_mapping_size(struct device *dev)
{
	const struct dma_map_ops *ops = get_dma_ops(dev);
	size_t size = SIZE_MAX;

	if (dma_is_direct(ops))
		size = dma_direct_max_mapping_size(dev);
	else if (ops && ops->max_mapping_size)
		size = ops->max_mapping_size(dev);

	return size;
}