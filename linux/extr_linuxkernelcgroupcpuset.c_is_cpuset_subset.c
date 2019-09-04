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
struct cpuset {int /*<<< orphan*/  mems_allowed; int /*<<< orphan*/  cpus_allowed; } ;

/* Variables and functions */
 scalar_t__ cpumask_subset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_cpu_exclusive (struct cpuset const*) ; 
 scalar_t__ is_mem_exclusive (struct cpuset const*) ; 
 scalar_t__ nodes_subset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int is_cpuset_subset(const struct cpuset *p, const struct cpuset *q)
{
	return	cpumask_subset(p->cpus_allowed, q->cpus_allowed) &&
		nodes_subset(p->mems_allowed, q->mems_allowed) &&
		is_cpu_exclusive(p) <= is_cpu_exclusive(q) &&
		is_mem_exclusive(p) <= is_mem_exclusive(q);
}