#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct perf_ftrace {int /*<<< orphan*/  target; TYPE_2__* evlist; } ;
struct perf_cpu_map {int dummy; } ;
struct TYPE_3__ {struct perf_cpu_map* cpus; } ;
struct TYPE_4__ {TYPE_1__ core; } ;

/* Variables and functions */
 int set_tracing_cpumask (struct perf_cpu_map*) ; 
 int /*<<< orphan*/  target__has_cpu (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int set_tracing_cpu(struct perf_ftrace *ftrace)
{
	struct perf_cpu_map *cpumap = ftrace->evlist->core.cpus;

	if (!target__has_cpu(&ftrace->target))
		return 0;

	return set_tracing_cpumask(cpumap);
}