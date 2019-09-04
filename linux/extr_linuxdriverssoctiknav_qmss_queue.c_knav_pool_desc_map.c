#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct knav_pool {int /*<<< orphan*/  dev; TYPE_1__* region; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  desc_size; } ;

/* Variables and functions */
 unsigned int ALIGN (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  SMP_CACHE_BYTES ; 
 int /*<<< orphan*/  __iowmb () ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  knav_pool_desc_virt_to_dma (struct knav_pool*,void*) ; 
 unsigned int min (unsigned int,int /*<<< orphan*/ ) ; 

int knav_pool_desc_map(void *ph, void *desc, unsigned size,
					dma_addr_t *dma, unsigned *dma_sz)
{
	struct knav_pool *pool = ph;
	*dma = knav_pool_desc_virt_to_dma(pool, desc);
	size = min(size, pool->region->desc_size);
	size = ALIGN(size, SMP_CACHE_BYTES);
	*dma_sz = size;
	dma_sync_single_for_device(pool->dev, *dma, size, DMA_TO_DEVICE);

	/* Ensure the descriptor reaches to the memory */
	__iowmb();

	return 0;
}