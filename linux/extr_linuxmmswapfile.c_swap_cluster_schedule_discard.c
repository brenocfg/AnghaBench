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
struct swap_info_struct {int /*<<< orphan*/  discard_work; int /*<<< orphan*/  cluster_info; int /*<<< orphan*/  discard_clusters; scalar_t__ swap_map; } ;

/* Variables and functions */
 unsigned int SWAPFILE_CLUSTER ; 
 int /*<<< orphan*/  SWAP_MAP_BAD ; 
 int /*<<< orphan*/  cluster_list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void swap_cluster_schedule_discard(struct swap_info_struct *si,
		unsigned int idx)
{
	/*
	 * If scan_swap_map() can't find a free cluster, it will check
	 * si->swap_map directly. To make sure the discarding cluster isn't
	 * taken by scan_swap_map(), mark the swap entries bad (occupied). It
	 * will be cleared after discard
	 */
	memset(si->swap_map + idx * SWAPFILE_CLUSTER,
			SWAP_MAP_BAD, SWAPFILE_CLUSTER);

	cluster_list_add_tail(&si->discard_clusters, si->cluster_info, idx);

	schedule_work(&si->discard_work);
}