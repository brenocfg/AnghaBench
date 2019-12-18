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

/* Variables and functions */
 int __dma_release_from_coherent (int /*<<< orphan*/ ,int,void*) ; 
 int /*<<< orphan*/  dma_coherent_default_memory ; 

int dma_release_from_global_coherent(int order, void *vaddr)
{
	if (!dma_coherent_default_memory)
		return 0;

	return __dma_release_from_coherent(dma_coherent_default_memory, order,
			vaddr);
}