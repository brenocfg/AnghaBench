#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cpupower_topology {scalar_t__ pkgs; TYPE_1__* core_info; scalar_t__ cores; } ;
struct cpuid_core_info {int dummy; } ;
struct TYPE_3__ {int cpu; int pkg; int core; int /*<<< orphan*/  is_online; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  _SC_NPROCESSORS_CONF ; 
 int /*<<< orphan*/  __compare ; 
 int /*<<< orphan*/  cpupower_is_cpu_online (int) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  qsort (TYPE_1__*,int,int,int /*<<< orphan*/ ) ; 
 int sysconf (int /*<<< orphan*/ ) ; 
 scalar_t__ sysfs_topology_read_file (int,char*,int*) ; 

int get_cpu_topology(struct cpupower_topology *cpu_top)
{
	int cpu, last_pkg, cpus = sysconf(_SC_NPROCESSORS_CONF);

	cpu_top->core_info = malloc(sizeof(struct cpuid_core_info) * cpus);
	if (cpu_top->core_info == NULL)
		return -ENOMEM;
	cpu_top->pkgs = cpu_top->cores = 0;
	for (cpu = 0; cpu < cpus; cpu++) {
		cpu_top->core_info[cpu].cpu = cpu;
		cpu_top->core_info[cpu].is_online = cpupower_is_cpu_online(cpu);
		if(sysfs_topology_read_file(
			cpu,
			"physical_package_id",
			&(cpu_top->core_info[cpu].pkg)) < 0) {
			cpu_top->core_info[cpu].pkg = -1;
			cpu_top->core_info[cpu].core = -1;
			continue;
		}
		if(sysfs_topology_read_file(
			cpu,
			"core_id",
			&(cpu_top->core_info[cpu].core)) < 0) {
			cpu_top->core_info[cpu].pkg = -1;
			cpu_top->core_info[cpu].core = -1;
			continue;
		}
	}

	qsort(cpu_top->core_info, cpus, sizeof(struct cpuid_core_info),
	      __compare);

	/* Count the number of distinct pkgs values. This works
	   because the primary sort of the core_info struct was just
	   done by pkg value. */
	last_pkg = cpu_top->core_info[0].pkg;
	for(cpu = 1; cpu < cpus; cpu++) {
		if (cpu_top->core_info[cpu].pkg != last_pkg &&
				cpu_top->core_info[cpu].pkg != -1) {

			last_pkg = cpu_top->core_info[cpu].pkg;
			cpu_top->pkgs++;
		}
	}
	if (!(cpu_top->core_info[0].pkg == -1))
		cpu_top->pkgs++;

	/* Intel's cores count is not consecutively numbered, there may
	 * be a core_id of 3, but none of 2. Assume there always is 0
	 * Get amount of cores by counting duplicates in a package
	for (cpu = 0; cpu_top->core_info[cpu].pkg = 0 && cpu < cpus; cpu++) {
		if (cpu_top->core_info[cpu].core == 0)
	cpu_top->cores++;
	*/
	return cpus;
}