#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct perf_ftrace {int /*<<< orphan*/  target; TYPE_1__* evlist; } ;
struct cpu_map {int dummy; } ;
struct TYPE_2__ {struct cpu_map* cpus; } ;

/* Variables and functions */
 int set_tracing_cpumask (struct cpu_map*) ; 
 int /*<<< orphan*/  target__has_cpu (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int set_tracing_cpu(struct perf_ftrace *ftrace)
{
	struct cpu_map *cpumap = ftrace->evlist->cpus;

	if (!target__has_cpu(&ftrace->target))
		return 0;

	return set_tracing_cpumask(cpumap);
}