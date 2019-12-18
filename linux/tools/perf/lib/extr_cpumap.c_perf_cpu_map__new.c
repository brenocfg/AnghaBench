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
 unsigned long INT_MAX ; 
 unsigned long MAX_NR_CPUS ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,unsigned long) ; 
 struct perf_cpu_map* cpu_map__default_new () ; 
 struct perf_cpu_map* cpu_map__read_all_cpu_map () ; 
 struct perf_cpu_map* cpu_map__trim_new (int,int*) ; 
 int /*<<< orphan*/  free (int*) ; 
 scalar_t__ isdigit (char const) ; 
 struct perf_cpu_map* perf_cpu_map__dummy_new () ; 
 int* realloc (int*,int) ; 
 unsigned long strtoul (char const*,char**,int /*<<< orphan*/ ) ; 

struct perf_cpu_map *perf_cpu_map__new(const char *cpu_list)
{
	struct perf_cpu_map *cpus = NULL;
	unsigned long start_cpu, end_cpu = 0;
	char *p = NULL;
	int i, nr_cpus = 0;
	int *tmp_cpus = NULL, *tmp;
	int max_entries = 0;

	if (!cpu_list)
		return cpu_map__read_all_cpu_map();

	/*
	 * must handle the case of empty cpumap to cover
	 * TOPOLOGY header for NUMA nodes with no CPU
	 * ( e.g., because of CPU hotplug)
	 */
	if (!isdigit(*cpu_list) && *cpu_list != '\0')
		goto out;

	while (isdigit(*cpu_list)) {
		p = NULL;
		start_cpu = strtoul(cpu_list, &p, 0);
		if (start_cpu >= INT_MAX
		    || (*p != '\0' && *p != ',' && *p != '-'))
			goto invalid;

		if (*p == '-') {
			cpu_list = ++p;
			p = NULL;
			end_cpu = strtoul(cpu_list, &p, 0);

			if (end_cpu >= INT_MAX || (*p != '\0' && *p != ','))
				goto invalid;

			if (end_cpu < start_cpu)
				goto invalid;
		} else {
			end_cpu = start_cpu;
		}

		WARN_ONCE(end_cpu >= MAX_NR_CPUS, "Perf can support %d CPUs. "
						  "Consider raising MAX_NR_CPUS\n", MAX_NR_CPUS);

		for (; start_cpu <= end_cpu; start_cpu++) {
			/* check for duplicates */
			for (i = 0; i < nr_cpus; i++)
				if (tmp_cpus[i] == (int)start_cpu)
					goto invalid;

			if (nr_cpus == max_entries) {
				max_entries += MAX_NR_CPUS;
				tmp = realloc(tmp_cpus, max_entries * sizeof(int));
				if (tmp == NULL)
					goto invalid;
				tmp_cpus = tmp;
			}
			tmp_cpus[nr_cpus++] = (int)start_cpu;
		}
		if (*p)
			++p;

		cpu_list = p;
	}

	if (nr_cpus > 0)
		cpus = cpu_map__trim_new(nr_cpus, tmp_cpus);
	else if (*cpu_list != '\0')
		cpus = cpu_map__default_new();
	else
		cpus = perf_cpu_map__dummy_new();
invalid:
	free(tmp_cpus);
out:
	return cpus;
}