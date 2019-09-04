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
struct page_pool {int dummy; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __page_pool_clean_page (struct page_pool*,struct page*) ; 
 scalar_t__ __page_pool_recycle_direct (struct page*,struct page_pool*) ; 
 int /*<<< orphan*/  __page_pool_recycle_into_ring (struct page_pool*,struct page*) ; 
 int /*<<< orphan*/  __page_pool_return_page (struct page_pool*,struct page*) ; 
 scalar_t__ in_serving_softirq () ; 
 scalar_t__ likely (int) ; 
 int page_ref_count (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 

void __page_pool_put_page(struct page_pool *pool,
			  struct page *page, bool allow_direct)
{
	/* This allocator is optimized for the XDP mode that uses
	 * one-frame-per-page, but have fallbacks that act like the
	 * regular page allocator APIs.
	 *
	 * refcnt == 1 means page_pool owns page, and can recycle it.
	 */
	if (likely(page_ref_count(page) == 1)) {
		/* Read barrier done in page_ref_count / READ_ONCE */

		if (allow_direct && in_serving_softirq())
			if (__page_pool_recycle_direct(page, pool))
				return;

		if (!__page_pool_recycle_into_ring(pool, page)) {
			/* Cache full, fallback to free pages */
			__page_pool_return_page(pool, page);
		}
		return;
	}
	/* Fallback/non-XDP mode: API user have elevated refcnt.
	 *
	 * Many drivers split up the page into fragments, and some
	 * want to keep doing this to save memory and do refcnt based
	 * recycling. Support this use case too, to ease drivers
	 * switching between XDP/non-XDP.
	 *
	 * In-case page_pool maintains the DMA mapping, API user must
	 * call page_pool_put_page once.  In this elevated refcnt
	 * case, the DMA is unmapped/released, as driver is likely
	 * doing refcnt based recycle tricks, meaning another process
	 * will be invoking put_page.
	 */
	__page_pool_clean_page(pool, page);
	put_page(page);
}