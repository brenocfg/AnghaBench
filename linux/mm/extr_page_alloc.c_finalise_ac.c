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
struct alloc_context {int spread_dirty_pages; int /*<<< orphan*/  nodemask; int /*<<< orphan*/  high_zoneidx; int /*<<< orphan*/  zonelist; int /*<<< orphan*/  preferred_zoneref; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int __GFP_WRITE ; 
 int /*<<< orphan*/  first_zones_zonelist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void finalise_ac(gfp_t gfp_mask, struct alloc_context *ac)
{
	/* Dirty zone balancing only done in the fast path */
	ac->spread_dirty_pages = (gfp_mask & __GFP_WRITE);

	/*
	 * The preferred zone is used for statistics but crucially it is
	 * also used as the starting point for the zonelist iterator. It
	 * may get reset for allocations that ignore memory policies.
	 */
	ac->preferred_zoneref = first_zones_zonelist(ac->zonelist,
					ac->high_zoneidx, ac->nodemask);
}