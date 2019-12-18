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
struct swap_info_struct {int /*<<< orphan*/  free_clusters; struct swap_cluster_info* cluster_info; } ;
struct swap_cluster_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int /*<<< orphan*/  cluster_list_del_first (int /*<<< orphan*/ *,struct swap_cluster_info*) ; 
 unsigned long cluster_list_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cluster_set_count_flag (struct swap_cluster_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void alloc_cluster(struct swap_info_struct *si, unsigned long idx)
{
	struct swap_cluster_info *ci = si->cluster_info;

	VM_BUG_ON(cluster_list_first(&si->free_clusters) != idx);
	cluster_list_del_first(&si->free_clusters, ci);
	cluster_set_count_flag(ci + idx, 0, 0);
}