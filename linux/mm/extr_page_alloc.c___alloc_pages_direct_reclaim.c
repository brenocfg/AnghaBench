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
struct page {int dummy; } ;
struct alloc_context {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 unsigned long __perform_reclaim (int /*<<< orphan*/ ,unsigned int,struct alloc_context const*) ; 
 int /*<<< orphan*/  drain_all_pages (int /*<<< orphan*/ *) ; 
 struct page* get_page_from_freelist (int /*<<< orphan*/ ,unsigned int,unsigned int,struct alloc_context const*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unreserve_highatomic_pageblock (struct alloc_context const*,int) ; 

__attribute__((used)) static inline struct page *
__alloc_pages_direct_reclaim(gfp_t gfp_mask, unsigned int order,
		unsigned int alloc_flags, const struct alloc_context *ac,
		unsigned long *did_some_progress)
{
	struct page *page = NULL;
	bool drained = false;

	*did_some_progress = __perform_reclaim(gfp_mask, order, ac);
	if (unlikely(!(*did_some_progress)))
		return NULL;

retry:
	page = get_page_from_freelist(gfp_mask, order, alloc_flags, ac);

	/*
	 * If an allocation failed after direct reclaim, it could be because
	 * pages are pinned on the per-cpu lists or in high alloc reserves.
	 * Shrink them them and try again
	 */
	if (!page && !drained) {
		unreserve_highatomic_pageblock(ac, false);
		drain_all_pages(NULL);
		drained = true;
		goto retry;
	}

	return page;
}