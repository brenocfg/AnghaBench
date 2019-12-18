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
struct ptr_ring {int /*<<< orphan*/  consumer_lock; } ;
struct TYPE_2__ {size_t count; struct page** cache; } ;
struct page_pool {TYPE_1__ alloc; struct ptr_ring ring; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PP_ALLOC_CACHE_REFILL ; 
 struct page* __ptr_ring_consume (struct ptr_ring*) ; 
 size_t __ptr_ring_consume_batched (struct ptr_ring*,struct page**,int /*<<< orphan*/ ) ; 
 scalar_t__ __ptr_ring_empty (struct ptr_ring*) ; 
 size_t in_serving_softirq () ; 
 scalar_t__ likely (size_t) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct page *__page_pool_get_cached(struct page_pool *pool)
{
	struct ptr_ring *r = &pool->ring;
	bool refill = false;
	struct page *page;

	/* Test for safe-context, caller should provide this guarantee */
	if (likely(in_serving_softirq())) {
		if (likely(pool->alloc.count)) {
			/* Fast-path */
			page = pool->alloc.cache[--pool->alloc.count];
			return page;
		}
		refill = true;
	}

	/* Quicker fallback, avoid locks when ring is empty */
	if (__ptr_ring_empty(r))
		return NULL;

	/* Slow-path: Get page from locked ring queue,
	 * refill alloc array if requested.
	 */
	spin_lock(&r->consumer_lock);
	page = __ptr_ring_consume(r);
	if (refill)
		pool->alloc.count = __ptr_ring_consume_batched(r,
							pool->alloc.cache,
							PP_ALLOC_CACHE_REFILL);
	spin_unlock(&r->consumer_lock);
	return page;
}