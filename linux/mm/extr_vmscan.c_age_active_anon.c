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
struct scan_control {int dummy; } ;
struct pglist_data {int dummy; } ;
struct mem_cgroup {int dummy; } ;
struct lruvec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LRU_ACTIVE_ANON ; 
 int /*<<< orphan*/  SWAP_CLUSTER_MAX ; 
 scalar_t__ inactive_list_is_low (struct lruvec*,int,struct scan_control*,int) ; 
 struct mem_cgroup* mem_cgroup_iter (int /*<<< orphan*/ *,struct mem_cgroup*,int /*<<< orphan*/ *) ; 
 struct lruvec* mem_cgroup_lruvec (struct pglist_data*,struct mem_cgroup*) ; 
 int /*<<< orphan*/  shrink_active_list (int /*<<< orphan*/ ,struct lruvec*,struct scan_control*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  total_swap_pages ; 

__attribute__((used)) static void age_active_anon(struct pglist_data *pgdat,
				struct scan_control *sc)
{
	struct mem_cgroup *memcg;

	if (!total_swap_pages)
		return;

	memcg = mem_cgroup_iter(NULL, NULL, NULL);
	do {
		struct lruvec *lruvec = mem_cgroup_lruvec(pgdat, memcg);

		if (inactive_list_is_low(lruvec, false, sc, true))
			shrink_active_list(SWAP_CLUSTER_MAX, lruvec,
					   sc, LRU_ACTIVE_ANON);

		memcg = mem_cgroup_iter(NULL, memcg, NULL);
	} while (memcg);
}