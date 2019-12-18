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
struct mem_cgroup_per_node {int /*<<< orphan*/  lruvec_stat_local; int /*<<< orphan*/  lruvec_stat_cpu; } ;
struct mem_cgroup {struct mem_cgroup_per_node** nodeinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mem_cgroup_per_node*) ; 

__attribute__((used)) static void free_mem_cgroup_per_node_info(struct mem_cgroup *memcg, int node)
{
	struct mem_cgroup_per_node *pn = memcg->nodeinfo[node];

	if (!pn)
		return;

	free_percpu(pn->lruvec_stat_cpu);
	free_percpu(pn->lruvec_stat_local);
	kfree(pn);
}