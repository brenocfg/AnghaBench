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
struct workqueue_attrs {int /*<<< orphan*/  cpumask; scalar_t__ no_numa; } ;
typedef  int /*<<< orphan*/  cpumask_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpumask_and (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_clear_cpu (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumask_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ cpumask_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumask_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_of_node (int) ; 
 int /*<<< orphan*/  pr_warn_once (char*) ; 
 int /*<<< orphan*/  wq_numa_enabled ; 
 int /*<<< orphan*/ * wq_numa_possible_cpumask ; 

__attribute__((used)) static bool wq_calc_node_cpumask(const struct workqueue_attrs *attrs, int node,
				 int cpu_going_down, cpumask_t *cpumask)
{
	if (!wq_numa_enabled || attrs->no_numa)
		goto use_dfl;

	/* does @node have any online CPUs @attrs wants? */
	cpumask_and(cpumask, cpumask_of_node(node), attrs->cpumask);
	if (cpu_going_down >= 0)
		cpumask_clear_cpu(cpu_going_down, cpumask);

	if (cpumask_empty(cpumask))
		goto use_dfl;

	/* yeap, return possible CPUs in @node that @attrs wants */
	cpumask_and(cpumask, attrs->cpumask, wq_numa_possible_cpumask[node]);

	if (cpumask_empty(cpumask)) {
		pr_warn_once("WARNING: workqueue cpumask: online intersect > "
				"possible intersect\n");
		return false;
	}

	return !cpumask_equal(cpumask, attrs->cpumask);

use_dfl:
	cpumask_copy(cpumask, attrs->cpumask);
	return false;
}