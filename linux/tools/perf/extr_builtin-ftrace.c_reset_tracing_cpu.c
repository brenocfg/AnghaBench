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
struct perf_cpu_map {int dummy; } ;

/* Variables and functions */
 struct perf_cpu_map* perf_cpu_map__new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_cpu_map__put (struct perf_cpu_map*) ; 
 int set_tracing_cpumask (struct perf_cpu_map*) ; 

__attribute__((used)) static int reset_tracing_cpu(void)
{
	struct perf_cpu_map *cpumap = perf_cpu_map__new(NULL);
	int ret;

	ret = set_tracing_cpumask(cpumap);
	perf_cpu_map__put(cpumap);
	return ret;
}