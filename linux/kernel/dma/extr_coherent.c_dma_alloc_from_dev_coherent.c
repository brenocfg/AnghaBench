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
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 void* __dma_alloc_from_coherent (struct dma_coherent_mem*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct dma_coherent_mem* dev_get_coherent_memory (struct device*) ; 

int dma_alloc_from_dev_coherent(struct device *dev, ssize_t size,
		dma_addr_t *dma_handle, void **ret)
{
	struct dma_coherent_mem *mem = dev_get_coherent_memory(dev);

	if (!mem)
		return 0;

	*ret = __dma_alloc_from_coherent(mem, size, dma_handle);
	return 1;
}