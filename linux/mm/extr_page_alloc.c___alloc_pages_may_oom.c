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
struct oom_control {int gfp_mask; unsigned int order; int /*<<< orphan*/ * memcg; int /*<<< orphan*/  nodemask; int /*<<< orphan*/  zonelist; } ;
struct alloc_context {scalar_t__ high_zoneidx; int /*<<< orphan*/  nodemask; int /*<<< orphan*/  zonelist; } ;
typedef  int gfp_t ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int ALLOC_CPUSET ; 
 int /*<<< orphan*/  ALLOC_NO_WATERMARKS ; 
 int ALLOC_WMARK_HIGH ; 
 unsigned int PAGE_ALLOC_COSTLY_ORDER ; 
 int PF_DUMPCORE ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 scalar_t__ ZONE_NORMAL ; 
 int __GFP_DIRECT_RECLAIM ; 
 int __GFP_HARDWALL ; 
 int __GFP_NOFAIL ; 
 int __GFP_RETRY_MAYFAIL ; 
 int __GFP_THISNODE ; 
 struct page* __alloc_pages_cpuset_fallback (int,unsigned int,int /*<<< orphan*/ ,struct alloc_context const*) ; 
 TYPE_1__* current ; 
 struct page* get_page_from_freelist (int,unsigned int,int,struct alloc_context const*) ; 
 int /*<<< orphan*/  mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oom_lock ; 
 scalar_t__ out_of_memory (struct oom_control*) ; 
 scalar_t__ pm_suspended_storage () ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 

__attribute__((used)) static inline struct page *
__alloc_pages_may_oom(gfp_t gfp_mask, unsigned int order,
	const struct alloc_context *ac, unsigned long *did_some_progress)
{
	struct oom_control oc = {
		.zonelist = ac->zonelist,
		.nodemask = ac->nodemask,
		.memcg = NULL,
		.gfp_mask = gfp_mask,
		.order = order,
	};
	struct page *page;

	*did_some_progress = 0;

	/*
	 * Acquire the oom lock.  If that fails, somebody else is
	 * making progress for us.
	 */
	if (!mutex_trylock(&oom_lock)) {
		*did_some_progress = 1;
		schedule_timeout_uninterruptible(1);
		return NULL;
	}

	/*
	 * Go through the zonelist yet one more time, keep very high watermark
	 * here, this is only to catch a parallel oom killing, we must fail if
	 * we're still under heavy pressure. But make sure that this reclaim
	 * attempt shall not depend on __GFP_DIRECT_RECLAIM && !__GFP_NORETRY
	 * allocation which will never fail due to oom_lock already held.
	 */
	page = get_page_from_freelist((gfp_mask | __GFP_HARDWALL) &
				      ~__GFP_DIRECT_RECLAIM, order,
				      ALLOC_WMARK_HIGH|ALLOC_CPUSET, ac);
	if (page)
		goto out;

	/* Coredumps can quickly deplete all memory reserves */
	if (current->flags & PF_DUMPCORE)
		goto out;
	/* The OOM killer will not help higher order allocs */
	if (order > PAGE_ALLOC_COSTLY_ORDER)
		goto out;
	/*
	 * We have already exhausted all our reclaim opportunities without any
	 * success so it is time to admit defeat. We will skip the OOM killer
	 * because it is very likely that the caller has a more reasonable
	 * fallback than shooting a random task.
	 */
	if (gfp_mask & __GFP_RETRY_MAYFAIL)
		goto out;
	/* The OOM killer does not needlessly kill tasks for lowmem */
	if (ac->high_zoneidx < ZONE_NORMAL)
		goto out;
	if (pm_suspended_storage())
		goto out;
	/*
	 * XXX: GFP_NOFS allocations should rather fail than rely on
	 * other request to make a forward progress.
	 * We are in an unfortunate situation where out_of_memory cannot
	 * do much for this context but let's try it to at least get
	 * access to memory reserved if the current task is killed (see
	 * out_of_memory). Once filesystems are ready to handle allocation
	 * failures more gracefully we should just bail out here.
	 */

	/* The OOM killer may not free memory on a specific node */
	if (gfp_mask & __GFP_THISNODE)
		goto out;

	/* Exhausted what can be done so it's blame time */
	if (out_of_memory(&oc) || WARN_ON_ONCE(gfp_mask & __GFP_NOFAIL)) {
		*did_some_progress = 1;

		/*
		 * Help non-failing allocations by giving them access to memory
		 * reserves
		 */
		if (gfp_mask & __GFP_NOFAIL)
			page = __alloc_pages_cpuset_fallback(gfp_mask, order,
					ALLOC_NO_WATERMARKS, ac);
	}
out:
	mutex_unlock(&oom_lock);
	return page;
}