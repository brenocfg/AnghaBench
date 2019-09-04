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
typedef  int /*<<< orphan*/  swp_entry_t ;
struct swap_info_struct {unsigned char* swap_map; int /*<<< orphan*/  type; int /*<<< orphan*/  free_clusters; } ;
struct swap_cluster_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLUSTER_FLAG_HUGE ; 
 int /*<<< orphan*/  CONFIG_THP_SWAP ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 unsigned long SWAPFILE_CLUSTER ; 
 unsigned char SWAP_HAS_CACHE ; 
 int /*<<< orphan*/  VM_WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  alloc_cluster (struct swap_info_struct*,unsigned long) ; 
 scalar_t__ cluster_list_empty (int /*<<< orphan*/ *) ; 
 unsigned long cluster_list_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cluster_set_count_flag (struct swap_cluster_info*,unsigned long,int /*<<< orphan*/ ) ; 
 struct swap_cluster_info* lock_cluster (struct swap_info_struct*,unsigned long) ; 
 int /*<<< orphan*/  swap_range_alloc (struct swap_info_struct*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  swp_entry (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  unlock_cluster (struct swap_cluster_info*) ; 

__attribute__((used)) static int swap_alloc_cluster(struct swap_info_struct *si, swp_entry_t *slot)
{
	unsigned long idx;
	struct swap_cluster_info *ci;
	unsigned long offset, i;
	unsigned char *map;

	/*
	 * Should not even be attempting cluster allocations when huge
	 * page swap is disabled.  Warn and fail the allocation.
	 */
	if (!IS_ENABLED(CONFIG_THP_SWAP)) {
		VM_WARN_ON_ONCE(1);
		return 0;
	}

	if (cluster_list_empty(&si->free_clusters))
		return 0;

	idx = cluster_list_first(&si->free_clusters);
	offset = idx * SWAPFILE_CLUSTER;
	ci = lock_cluster(si, offset);
	alloc_cluster(si, idx);
	cluster_set_count_flag(ci, SWAPFILE_CLUSTER, CLUSTER_FLAG_HUGE);

	map = si->swap_map + offset;
	for (i = 0; i < SWAPFILE_CLUSTER; i++)
		map[i] = SWAP_HAS_CACHE;
	unlock_cluster(ci);
	swap_range_alloc(si, offset, SWAPFILE_CLUSTER);
	*slot = swp_entry(si->type, offset);

	return 1;
}