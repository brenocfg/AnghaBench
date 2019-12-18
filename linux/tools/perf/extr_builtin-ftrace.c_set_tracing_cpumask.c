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
struct perf_cpu_map {scalar_t__ nr; } ;

/* Variables and functions */
 int cpu_map__cpu (struct perf_cpu_map*,scalar_t__) ; 
 int /*<<< orphan*/  cpu_map__snprint_mask (struct perf_cpu_map*,char*,size_t) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int write_tracing_file (char*,char*) ; 

__attribute__((used)) static int set_tracing_cpumask(struct perf_cpu_map *cpumap)
{
	char *cpumask;
	size_t mask_size;
	int ret;
	int last_cpu;

	last_cpu = cpu_map__cpu(cpumap, cpumap->nr - 1);
	mask_size = last_cpu / 4 + 2; /* one more byte for EOS */
	mask_size += last_cpu / 32; /* ',' is needed for every 32th cpus */

	cpumask = malloc(mask_size);
	if (cpumask == NULL) {
		pr_debug("failed to allocate cpu mask\n");
		return -1;
	}

	cpu_map__snprint_mask(cpumap, cpumask, mask_size);

	ret = write_tracing_file("tracing_cpumask", cpumask);

	free(cpumask);
	return ret;
}