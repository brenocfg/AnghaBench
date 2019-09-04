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
struct device {struct dma_coherent_mem* dma_mem; } ;

/* Variables and functions */

__attribute__((used)) static inline struct dma_coherent_mem *dev_get_coherent_memory(struct device *dev)
{
	if (dev && dev->dma_mem)
		return dev->dma_mem;
	return NULL;
}