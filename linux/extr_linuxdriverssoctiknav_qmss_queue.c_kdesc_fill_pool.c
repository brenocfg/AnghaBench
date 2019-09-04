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
struct knav_region {int desc_size; scalar_t__ dma_start; } ;
struct knav_pool {int desc_size; int num_desc; int region_offset; int /*<<< orphan*/  queue; int /*<<< orphan*/  dev; struct knav_region* region; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 unsigned int ALIGN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  SMP_CACHE_BYTES ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ ,scalar_t__,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  knav_queue_push (int /*<<< orphan*/ ,scalar_t__,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kdesc_fill_pool(struct knav_pool *pool)
{
	struct knav_region *region;
	int i;

	region = pool->region;
	pool->desc_size = region->desc_size;
	for (i = 0; i < pool->num_desc; i++) {
		int index = pool->region_offset + i;
		dma_addr_t dma_addr;
		unsigned dma_size;
		dma_addr = region->dma_start + (region->desc_size * index);
		dma_size = ALIGN(pool->desc_size, SMP_CACHE_BYTES);
		dma_sync_single_for_device(pool->dev, dma_addr, dma_size,
					   DMA_TO_DEVICE);
		knav_queue_push(pool->queue, dma_addr, dma_size, 0);
	}
}