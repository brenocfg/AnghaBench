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
struct dma_coherent_mem {int pfn_base; int device_base; scalar_t__ use_dev_dma_pfn_offset; } ;
struct device {int dma_pfn_offset; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int PAGE_SHIFT ; 

__attribute__((used)) static inline dma_addr_t dma_get_device_base(struct device *dev,
					     struct dma_coherent_mem * mem)
{
	if (mem->use_dev_dma_pfn_offset)
		return (mem->pfn_base - dev->dma_pfn_offset) << PAGE_SHIFT;
	else
		return mem->device_base;
}