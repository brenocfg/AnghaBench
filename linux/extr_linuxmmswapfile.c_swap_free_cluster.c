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
struct swap_info_struct {int dummy; } ;
struct swap_cluster_info {int dummy; } ;

/* Variables and functions */
 unsigned long SWAPFILE_CLUSTER ; 
 int /*<<< orphan*/  cluster_set_count_flag (struct swap_cluster_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_cluster (struct swap_info_struct*,unsigned long) ; 
 struct swap_cluster_info* lock_cluster (struct swap_info_struct*,unsigned long) ; 
 int /*<<< orphan*/  swap_range_free (struct swap_info_struct*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  unlock_cluster (struct swap_cluster_info*) ; 

__attribute__((used)) static void swap_free_cluster(struct swap_info_struct *si, unsigned long idx)
{
	unsigned long offset = idx * SWAPFILE_CLUSTER;
	struct swap_cluster_info *ci;

	ci = lock_cluster(si, offset);
	cluster_set_count_flag(ci, 0, 0);
	free_cluster(si, idx);
	unlock_cluster(ci);
	swap_range_free(si, offset, SWAPFILE_CLUSTER);
}