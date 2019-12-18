#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int flags; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int count; } ;
struct page_pool {TYPE_2__ p; int /*<<< orphan*/  ring; TYPE_1__ alloc; } ;

/* Variables and functions */
 int PP_FLAG_DMA_MAP ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  __page_pool_safe_to_destroy (struct page_pool*) ; 
 int /*<<< orphan*/  __warn_in_flight (struct page_pool*) ; 
 int /*<<< orphan*/  kfree (struct page_pool*) ; 
 int /*<<< orphan*/  page_pool_put (struct page_pool*) ; 
 int /*<<< orphan*/  ptr_ring_cleanup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptr_ring_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ ) ; 

void __page_pool_free(struct page_pool *pool)
{
	/* Only last user actually free/release resources */
	if (!page_pool_put(pool))
		return;

	WARN(pool->alloc.count, "API usage violation");
	WARN(!ptr_ring_empty(&pool->ring), "ptr_ring is not empty");

	/* Can happen due to forced shutdown */
	if (!__page_pool_safe_to_destroy(pool))
		__warn_in_flight(pool);

	ptr_ring_cleanup(&pool->ring, NULL);

	if (pool->p.flags & PP_FLAG_DMA_MAP)
		put_device(pool->p.dev);

	kfree(pool);
}