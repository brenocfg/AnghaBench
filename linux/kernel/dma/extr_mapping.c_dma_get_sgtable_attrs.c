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
struct sg_table {int dummy; } ;
struct dma_map_ops {int (* get_sgtable ) (struct device*,struct sg_table*,void*,int /*<<< orphan*/ ,size_t,unsigned long) ;} ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int ENXIO ; 
 int dma_common_get_sgtable (struct device*,struct sg_table*,void*,int /*<<< orphan*/ ,size_t,unsigned long) ; 
 scalar_t__ dma_is_direct (struct dma_map_ops const*) ; 
 struct dma_map_ops* get_dma_ops (struct device*) ; 
 int stub1 (struct device*,struct sg_table*,void*,int /*<<< orphan*/ ,size_t,unsigned long) ; 

int dma_get_sgtable_attrs(struct device *dev, struct sg_table *sgt,
		void *cpu_addr, dma_addr_t dma_addr, size_t size,
		unsigned long attrs)
{
	const struct dma_map_ops *ops = get_dma_ops(dev);

	if (dma_is_direct(ops))
		return dma_common_get_sgtable(dev, sgt, cpu_addr, dma_addr,
				size, attrs);
	if (!ops->get_sgtable)
		return -ENXIO;
	return ops->get_sgtable(dev, sgt, cpu_addr, dma_addr, size, attrs);
}