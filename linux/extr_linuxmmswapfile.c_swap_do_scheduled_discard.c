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
struct swap_info_struct {scalar_t__ swap_map; int /*<<< orphan*/  lock; int /*<<< orphan*/  discard_clusters; struct swap_cluster_info* cluster_info; } ;
struct swap_cluster_info {int dummy; } ;

/* Variables and functions */
 unsigned int SWAPFILE_CLUSTER ; 
 int /*<<< orphan*/  __free_cluster (struct swap_info_struct*,unsigned int) ; 
 unsigned int cluster_list_del_first (int /*<<< orphan*/ *,struct swap_cluster_info*) ; 
 int /*<<< orphan*/  cluster_list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  discard_swap_cluster (struct swap_info_struct*,unsigned int,unsigned int) ; 
 struct swap_cluster_info* lock_cluster (struct swap_info_struct*,unsigned int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_cluster (struct swap_cluster_info*) ; 

__attribute__((used)) static void swap_do_scheduled_discard(struct swap_info_struct *si)
{
	struct swap_cluster_info *info, *ci;
	unsigned int idx;

	info = si->cluster_info;

	while (!cluster_list_empty(&si->discard_clusters)) {
		idx = cluster_list_del_first(&si->discard_clusters, info);
		spin_unlock(&si->lock);

		discard_swap_cluster(si, idx * SWAPFILE_CLUSTER,
				SWAPFILE_CLUSTER);

		spin_lock(&si->lock);
		ci = lock_cluster(si, idx * SWAPFILE_CLUSTER);
		__free_cluster(si, idx);
		memset(si->swap_map + idx * SWAPFILE_CLUSTER,
				0, SWAPFILE_CLUSTER);
		unlock_cluster(ci);
	}
}