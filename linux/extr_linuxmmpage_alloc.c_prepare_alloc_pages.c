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
struct alloc_context {int /*<<< orphan*/  migratetype; int /*<<< orphan*/ * nodemask; int /*<<< orphan*/  zonelist; int /*<<< orphan*/  high_zoneidx; } ;
typedef  int /*<<< orphan*/  nodemask_t ;
typedef  int gfp_t ;

/* Variables and functions */
 unsigned int ALLOC_CMA ; 
 unsigned int ALLOC_CPUSET ; 
 int /*<<< orphan*/  CONFIG_CMA ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIGRATE_MOVABLE ; 
 int __GFP_DIRECT_RECLAIM ; 
 int __GFP_HARDWALL ; 
 int /*<<< orphan*/  cpuset_current_mems_allowed ; 
 scalar_t__ cpusets_enabled () ; 
 int /*<<< orphan*/  fs_reclaim_acquire (int) ; 
 int /*<<< orphan*/  fs_reclaim_release (int) ; 
 int /*<<< orphan*/  gfp_zone (int) ; 
 int /*<<< orphan*/  gfpflags_to_migratetype (int) ; 
 int /*<<< orphan*/  might_sleep_if (int) ; 
 int /*<<< orphan*/  node_zonelist (int,int) ; 
 scalar_t__ should_fail_alloc_page (int,unsigned int) ; 

__attribute__((used)) static inline bool prepare_alloc_pages(gfp_t gfp_mask, unsigned int order,
		int preferred_nid, nodemask_t *nodemask,
		struct alloc_context *ac, gfp_t *alloc_mask,
		unsigned int *alloc_flags)
{
	ac->high_zoneidx = gfp_zone(gfp_mask);
	ac->zonelist = node_zonelist(preferred_nid, gfp_mask);
	ac->nodemask = nodemask;
	ac->migratetype = gfpflags_to_migratetype(gfp_mask);

	if (cpusets_enabled()) {
		*alloc_mask |= __GFP_HARDWALL;
		if (!ac->nodemask)
			ac->nodemask = &cpuset_current_mems_allowed;
		else
			*alloc_flags |= ALLOC_CPUSET;
	}

	fs_reclaim_acquire(gfp_mask);
	fs_reclaim_release(gfp_mask);

	might_sleep_if(gfp_mask & __GFP_DIRECT_RECLAIM);

	if (should_fail_alloc_page(gfp_mask, order))
		return false;

	if (IS_ENABLED(CONFIG_CMA) && ac->migratetype == MIGRATE_MOVABLE)
		*alloc_flags |= ALLOC_CMA;

	return true;
}