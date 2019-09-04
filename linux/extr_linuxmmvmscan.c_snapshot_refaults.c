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
struct mem_cgroup {int dummy; } ;
struct lruvec {unsigned long refaults; } ;
typedef  int /*<<< orphan*/  pg_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  WORKINGSET_ACTIVATE ; 
 struct mem_cgroup* mem_cgroup_iter (struct mem_cgroup*,struct mem_cgroup*,int /*<<< orphan*/ *) ; 
 struct lruvec* mem_cgroup_lruvec (int /*<<< orphan*/ *,struct mem_cgroup*) ; 
 unsigned long memcg_page_state (struct mem_cgroup*,int /*<<< orphan*/ ) ; 
 unsigned long node_page_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snapshot_refaults(struct mem_cgroup *root_memcg, pg_data_t *pgdat)
{
	struct mem_cgroup *memcg;

	memcg = mem_cgroup_iter(root_memcg, NULL, NULL);
	do {
		unsigned long refaults;
		struct lruvec *lruvec;

		if (memcg)
			refaults = memcg_page_state(memcg, WORKINGSET_ACTIVATE);
		else
			refaults = node_page_state(pgdat, WORKINGSET_ACTIVATE);

		lruvec = mem_cgroup_lruvec(pgdat, memcg);
		lruvec->refaults = refaults;
	} while ((memcg = mem_cgroup_iter(root_memcg, memcg, NULL)));
}