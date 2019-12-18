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
 char* CPUS_TEMPLATE_UNCORE ; 
 int PATH_MAX ; 
 struct perf_cpu_map* __pmu_cpumask (char*) ; 
 int /*<<< orphan*/  perf_cpu_map__put (struct perf_cpu_map*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char const*) ; 
 char* sysfs__mountpoint () ; 

__attribute__((used)) static bool pmu_is_uncore(const char *name)
{
	char path[PATH_MAX];
	struct perf_cpu_map *cpus;
	const char *sysfs = sysfs__mountpoint();

	snprintf(path, PATH_MAX, CPUS_TEMPLATE_UNCORE, sysfs, name);
	cpus = __pmu_cpumask(path);
	perf_cpu_map__put(cpus);

	return !!cpus;
}