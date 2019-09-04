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
struct swap_info_struct {int /*<<< orphan*/  percpu_cluster; int /*<<< orphan*/ * cluster_info; int /*<<< orphan*/  free_clusters; } ;
struct percpu_cluster {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 unsigned long SWAPFILE_CLUSTER ; 
 scalar_t__ cluster_is_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cluster_list_empty (int /*<<< orphan*/ *) ; 
 unsigned long cluster_list_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cluster_set_null (int /*<<< orphan*/ *) ; 
 struct percpu_cluster* this_cpu_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
scan_swap_map_ssd_cluster_conflict(struct swap_info_struct *si,
	unsigned long offset)
{
	struct percpu_cluster *percpu_cluster;
	bool conflict;

	offset /= SWAPFILE_CLUSTER;
	conflict = !cluster_list_empty(&si->free_clusters) &&
		offset != cluster_list_first(&si->free_clusters) &&
		cluster_is_free(&si->cluster_info[offset]);

	if (!conflict)
		return false;

	percpu_cluster = this_cpu_ptr(si->percpu_cluster);
	cluster_set_null(&percpu_cluster->index);
	return true;
}