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
struct mem_cgroup_reclaim_cookie {int /*<<< orphan*/  priority; int /*<<< orphan*/ * pgdat; } ;
struct mem_cgroup {int dummy; } ;
typedef  int /*<<< orphan*/  pg_data_t ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int MEM_CGROUP_MAX_RECLAIM_LOOPS ; 
 struct mem_cgroup* mem_cgroup_iter (struct mem_cgroup*,struct mem_cgroup*,struct mem_cgroup_reclaim_cookie*) ; 
 int /*<<< orphan*/  mem_cgroup_iter_break (struct mem_cgroup*,struct mem_cgroup*) ; 
 scalar_t__ mem_cgroup_shrink_node (struct mem_cgroup*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,unsigned long*) ; 
 unsigned long soft_limit_excess (struct mem_cgroup*) ; 

__attribute__((used)) static int mem_cgroup_soft_reclaim(struct mem_cgroup *root_memcg,
				   pg_data_t *pgdat,
				   gfp_t gfp_mask,
				   unsigned long *total_scanned)
{
	struct mem_cgroup *victim = NULL;
	int total = 0;
	int loop = 0;
	unsigned long excess;
	unsigned long nr_scanned;
	struct mem_cgroup_reclaim_cookie reclaim = {
		.pgdat = pgdat,
		.priority = 0,
	};

	excess = soft_limit_excess(root_memcg);

	while (1) {
		victim = mem_cgroup_iter(root_memcg, victim, &reclaim);
		if (!victim) {
			loop++;
			if (loop >= 2) {
				/*
				 * If we have not been able to reclaim
				 * anything, it might because there are
				 * no reclaimable pages under this hierarchy
				 */
				if (!total)
					break;
				/*
				 * We want to do more targeted reclaim.
				 * excess >> 2 is not to excessive so as to
				 * reclaim too much, nor too less that we keep
				 * coming back to reclaim from this cgroup
				 */
				if (total >= (excess >> 2) ||
					(loop > MEM_CGROUP_MAX_RECLAIM_LOOPS))
					break;
			}
			continue;
		}
		total += mem_cgroup_shrink_node(victim, gfp_mask, false,
					pgdat, &nr_scanned);
		*total_scanned += nr_scanned;
		if (!soft_limit_excess(root_memcg))
			break;
	}
	mem_cgroup_iter_break(root_memcg, victim);
	return total;
}