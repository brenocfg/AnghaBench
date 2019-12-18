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
struct sw_flow_stats {int /*<<< orphan*/  lock; } ;
struct sw_flow {int stats_last_writer; int /*<<< orphan*/  cpu_used_mask; int /*<<< orphan*/ * stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct sw_flow* ERR_PTR (int /*<<< orphan*/ ) ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  NUMA_NO_NODE ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,struct sw_flow_stats*) ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  cpumask_set_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flow_cache ; 
 int /*<<< orphan*/  flow_stats_cache ; 
 struct sw_flow_stats* kmem_cache_alloc_node (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct sw_flow*) ; 
 struct sw_flow* kmem_cache_zalloc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ node_online (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct sw_flow *ovs_flow_alloc(void)
{
	struct sw_flow *flow;
	struct sw_flow_stats *stats;

	flow = kmem_cache_zalloc(flow_cache, GFP_KERNEL);
	if (!flow)
		return ERR_PTR(-ENOMEM);

	flow->stats_last_writer = -1;

	/* Initialize the default stat node. */
	stats = kmem_cache_alloc_node(flow_stats_cache,
				      GFP_KERNEL | __GFP_ZERO,
				      node_online(0) ? 0 : NUMA_NO_NODE);
	if (!stats)
		goto err;

	spin_lock_init(&stats->lock);

	RCU_INIT_POINTER(flow->stats[0], stats);

	cpumask_set_cpu(0, &flow->cpu_used_mask);

	return flow;
err:
	kmem_cache_free(flow_cache, flow);
	return ERR_PTR(-ENOMEM);
}