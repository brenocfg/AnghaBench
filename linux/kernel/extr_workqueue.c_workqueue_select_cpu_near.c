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

/* Variables and functions */
 int MAX_NUMNODES ; 
 int WORK_CPU_UNBOUND ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 int cpu_to_node (int) ; 
 int cpumask_any_and (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_of_node (int) ; 
 int /*<<< orphan*/  node_online (int) ; 
 int nr_cpu_ids ; 
 int raw_smp_processor_id () ; 
 int /*<<< orphan*/  wq_numa_enabled ; 

__attribute__((used)) static int workqueue_select_cpu_near(int node)
{
	int cpu;

	/* No point in doing this if NUMA isn't enabled for workqueues */
	if (!wq_numa_enabled)
		return WORK_CPU_UNBOUND;

	/* Delay binding to CPU if node is not valid or online */
	if (node < 0 || node >= MAX_NUMNODES || !node_online(node))
		return WORK_CPU_UNBOUND;

	/* Use local node/cpu if we are already there */
	cpu = raw_smp_processor_id();
	if (node == cpu_to_node(cpu))
		return cpu;

	/* Use "random" otherwise know as "first" online CPU of node */
	cpu = cpumask_any_and(cpumask_of_node(node), cpu_online_mask);

	/* If CPU is valid return that, otherwise just defer */
	return cpu < nr_cpu_ids ? cpu : WORK_CPU_UNBOUND;
}