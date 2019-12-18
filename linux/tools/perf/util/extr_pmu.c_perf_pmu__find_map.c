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
struct pmu_events_map {int /*<<< orphan*/  cpuid; int /*<<< orphan*/  table; } ;
struct perf_pmu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* perf_pmu__getcpuid (struct perf_pmu*) ; 
 struct pmu_events_map* pmu_events_map ; 
 int /*<<< orphan*/  strcmp_cpuid_str (int /*<<< orphan*/ ,char*) ; 

struct pmu_events_map *perf_pmu__find_map(struct perf_pmu *pmu)
{
	struct pmu_events_map *map;
	char *cpuid = perf_pmu__getcpuid(pmu);
	int i;

	/* on some platforms which uses cpus map, cpuid can be NULL for
	 * PMUs other than CORE PMUs.
	 */
	if (!cpuid)
		return NULL;

	i = 0;
	for (;;) {
		map = &pmu_events_map[i++];
		if (!map->table) {
			map = NULL;
			break;
		}

		if (!strcmp_cpuid_str(map->cpuid, cpuid))
			break;
	}
	free(cpuid);
	return map;
}