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
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int /*<<< orphan*/  alloc_cluster (struct swap_info_struct*,unsigned long) ; 
 int cluster_count (struct swap_cluster_info*) ; 
 scalar_t__ cluster_is_free (struct swap_cluster_info*) ; 
 int /*<<< orphan*/  cluster_set_count (struct swap_cluster_info*,int) ; 

__attribute__((used)) static void inc_cluster_info_page(struct swap_info_struct *p,
	struct swap_cluster_info *cluster_info, unsigned long page_nr)
{
	unsigned long idx = page_nr / SWAPFILE_CLUSTER;

	if (!cluster_info)
		return;
	if (cluster_is_free(&cluster_info[idx]))
		alloc_cluster(p, idx);

	VM_BUG_ON(cluster_count(&cluster_info[idx]) >= SWAPFILE_CLUSTER);
	cluster_set_count(&cluster_info[idx],
		cluster_count(&cluster_info[idx]) + 1);
}