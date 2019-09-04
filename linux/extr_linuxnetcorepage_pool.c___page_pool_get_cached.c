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
struct page_pool {struct ptr_ring ring; TYPE_1__ alloc; } ;
struct page {int dummy; } ;

/* Variables and functions */
 size_t PP_ALLOC_CACHE_REFILL ; 
 struct page* __ptr_ring_consume (struct ptr_ring*) ; 
 scalar_t__ __ptr_ring_empty (struct ptr_ring*) ; 
 size_t in_serving_softirq () ; 
 scalar_t__ likely (size_t) ; 
 struct page* ptr_ring_consume (struct ptr_ring*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct page *__page_pool_get_cached(struct page_pool *pool)
{
	struct ptr_ring *r = &pool->ring;
	struct page *page;

	/* Quicker fallback, avoid locks when ring is empty */
	if (__ptr_ring_empty(r))
		return NULL;

	/* Test for safe-context, caller should provide this guarantee */
	if (likely(in_serving_softirq())) {
		if (likely(pool->alloc.count)) {
			/* Fast-path */
			page = pool->alloc.cache[--pool->alloc.count];
			return page;
		}
		/* Slower-path: Alloc array empty, time to refill
		 *
		 * Open-coded bulk ptr_ring consumer.
		 *
		 * Discussion: the ring consumer lock is not really
		 * needed due to the softirq/NAPI protection, but
		 * later need the ability to reclaim pages on the
		 * ring. Thus, keeping the locks.
		 */
		spin_lock(&r->consumer_lock);
		while ((page = __ptr_ring_consume(r))) {
			if (pool->alloc.count == PP_ALLOC_CACHE_REFILL)
				break;
			pool->alloc.cache[pool->alloc.count++] = page;
		}
		spin_unlock(&r->consumer_lock);
		return page;
	}

	/* Slow-path: Get page from locked ring queue */
	page = ptr_ring_consume(&pool->ring);
	return page;
}