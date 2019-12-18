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
struct page {int dummy; } ;
struct alloc_context {int spread_dirty_pages; int /*<<< orphan*/  migratetype; int /*<<< orphan*/ * nodemask; TYPE_1__* preferred_zoneref; } ;
typedef  int /*<<< orphan*/  nodemask_t ;
typedef  int gfp_t ;
struct TYPE_2__ {int /*<<< orphan*/  zone; } ;

/* Variables and functions */
 unsigned int ALLOC_WMARK_LOW ; 
 unsigned int MAX_ORDER ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int __GFP_ACCOUNT ; 
 int __GFP_NOWARN ; 
 struct page* __alloc_pages_slowpath (int,unsigned int,struct alloc_context*) ; 
 int /*<<< orphan*/  __free_pages (struct page*,unsigned int) ; 
 scalar_t__ __memcg_kmem_charge (struct page*,int,unsigned int) ; 
 unsigned int alloc_flags_nofragment (int /*<<< orphan*/ ,int) ; 
 int current_gfp_context (int) ; 
 int /*<<< orphan*/  finalise_ac (int,struct alloc_context*) ; 
 struct page* get_page_from_freelist (int,unsigned int,unsigned int,struct alloc_context*) ; 
 int gfp_allowed_mask ; 
 scalar_t__ likely (struct page*) ; 
 scalar_t__ memcg_kmem_enabled () ; 
 int /*<<< orphan*/  prepare_alloc_pages (int,unsigned int,int,int /*<<< orphan*/ *,struct alloc_context*,int*,unsigned int*) ; 
 int /*<<< orphan*/  trace_mm_page_alloc (struct page*,unsigned int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

struct page *
__alloc_pages_nodemask(gfp_t gfp_mask, unsigned int order, int preferred_nid,
							nodemask_t *nodemask)
{
	struct page *page;
	unsigned int alloc_flags = ALLOC_WMARK_LOW;
	gfp_t alloc_mask; /* The gfp_t that was actually used for allocation */
	struct alloc_context ac = { };

	/*
	 * There are several places where we assume that the order value is sane
	 * so bail out early if the request is out of bound.
	 */
	if (unlikely(order >= MAX_ORDER)) {
		WARN_ON_ONCE(!(gfp_mask & __GFP_NOWARN));
		return NULL;
	}

	gfp_mask &= gfp_allowed_mask;
	alloc_mask = gfp_mask;
	if (!prepare_alloc_pages(gfp_mask, order, preferred_nid, nodemask, &ac, &alloc_mask, &alloc_flags))
		return NULL;

	finalise_ac(gfp_mask, &ac);

	/*
	 * Forbid the first pass from falling back to types that fragment
	 * memory until all local zones are considered.
	 */
	alloc_flags |= alloc_flags_nofragment(ac.preferred_zoneref->zone, gfp_mask);

	/* First allocation attempt */
	page = get_page_from_freelist(alloc_mask, order, alloc_flags, &ac);
	if (likely(page))
		goto out;

	/*
	 * Apply scoped allocation constraints. This is mainly about GFP_NOFS
	 * resp. GFP_NOIO which has to be inherited for all allocation requests
	 * from a particular context which has been marked by
	 * memalloc_no{fs,io}_{save,restore}.
	 */
	alloc_mask = current_gfp_context(gfp_mask);
	ac.spread_dirty_pages = false;

	/*
	 * Restore the original nodemask if it was potentially replaced with
	 * &cpuset_current_mems_allowed to optimize the fast-path attempt.
	 */
	if (unlikely(ac.nodemask != nodemask))
		ac.nodemask = nodemask;

	page = __alloc_pages_slowpath(alloc_mask, order, &ac);

out:
	if (memcg_kmem_enabled() && (gfp_mask & __GFP_ACCOUNT) && page &&
	    unlikely(__memcg_kmem_charge(page, gfp_mask, order) != 0)) {
		__free_pages(page, order);
		page = NULL;
	}

	trace_mm_page_alloc(page, order, alloc_mask, ac.migratetype);

	return page;
}