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
struct knav_pool {int /*<<< orphan*/  queue; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 void* knav_pool_desc_dma_to_virt (struct knav_pool*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  knav_queue_pop (int /*<<< orphan*/ ,unsigned int*) ; 
 scalar_t__ unlikely (int) ; 

void *knav_pool_desc_get(void *ph)
{
	struct knav_pool *pool = ph;
	dma_addr_t dma;
	unsigned size;
	void *data;

	dma = knav_queue_pop(pool->queue, &size);
	if (unlikely(!dma))
		return ERR_PTR(-ENOMEM);
	data = knav_pool_desc_dma_to_virt(pool, dma);
	return data;
}