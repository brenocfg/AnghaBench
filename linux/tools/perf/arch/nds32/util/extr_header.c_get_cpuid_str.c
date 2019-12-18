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
struct perf_pmu {int /*<<< orphan*/  cpus; } ;
struct cpu_map {int nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  STR_LEN ; 
 struct cpu_map* cpu_map__get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_map__put (struct cpu_map*) ; 
 char* malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 char* sysfs__mountpoint () ; 

char *get_cpuid_str(struct perf_pmu *pmu)
{
	/* In nds32, we only have one cpu */
	char *buf = NULL;
	struct cpu_map *cpus;
	const char *sysfs = sysfs__mountpoint();

	if (!sysfs || !pmu || !pmu->cpus)
		return NULL;

	buf = malloc(STR_LEN);
	if (!buf)
		return NULL;

	cpus = cpu_map__get(pmu->cpus);
	sprintf(buf, "0x%x", cpus->nr - 1);
	cpu_map__put(cpus);
	return buf;
}