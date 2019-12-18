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
struct sw_flow_stats {int /*<<< orphan*/  lock; scalar_t__ tcp_flags; scalar_t__ byte_count; scalar_t__ packet_count; scalar_t__ used; } ;
struct sw_flow {int /*<<< orphan*/ * stats; int /*<<< orphan*/  cpu_used_mask; } ;

/* Variables and functions */
 int cpumask_next (int,int /*<<< orphan*/ *) ; 
 int nr_cpu_ids ; 
 struct sw_flow_stats* ovsl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void ovs_flow_stats_clear(struct sw_flow *flow)
{
	int cpu;

	/* We open code this to make sure cpu 0 is always considered */
	for (cpu = 0; cpu < nr_cpu_ids; cpu = cpumask_next(cpu, &flow->cpu_used_mask)) {
		struct sw_flow_stats *stats = ovsl_dereference(flow->stats[cpu]);

		if (stats) {
			spin_lock_bh(&stats->lock);
			stats->used = 0;
			stats->packet_count = 0;
			stats->byte_count = 0;
			stats->tcp_flags = 0;
			spin_unlock_bh(&stats->lock);
		}
	}
}