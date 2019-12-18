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
struct dma_coherent_mem {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int __dma_release_from_coherent (struct dma_coherent_mem*,int,void*) ; 
 struct dma_coherent_mem* dev_get_coherent_memory (struct device*) ; 

int dma_release_from_dev_coherent(struct device *dev, int order, void *vaddr)
{
	struct dma_coherent_mem *mem = dev_get_coherent_memory(dev);

	return __dma_release_from_coherent(mem, order, vaddr);
}