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
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_SET_S (int,size_t,int /*<<< orphan*/ ) ; 
 int MAX_DIE_PER_PACKAGE ; 
 int MAX_PACKAGE_COUNT ; 
 size_t alloc_cpu_set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** cpu_cnt ; 
 int get_physical_die_id (int) ; 
 int get_physical_package_id (int) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 int /*<<< orphan*/  present_cpumask ; 
 size_t present_cpumask_size ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int topo_max_cpus ; 

__attribute__((used)) static void set_cpu_present_cpu_mask(void)
{
	size_t size;
	DIR *dir;
	int i;

	size = alloc_cpu_set(&present_cpumask);
	present_cpumask_size = size;
	for (i = 0; i < topo_max_cpus; ++i) {
		char buffer[256];

		snprintf(buffer, sizeof(buffer),
			 "/sys/devices/system/cpu/cpu%d", i);
		dir = opendir(buffer);
		if (dir) {
			int pkg_id, die_id;

			CPU_SET_S(i, size, present_cpumask);
			die_id = get_physical_die_id(i);
			if (die_id < 0)
				die_id = 0;

			pkg_id = get_physical_package_id(i);
			if (pkg_id < MAX_PACKAGE_COUNT &&
			    die_id < MAX_DIE_PER_PACKAGE)
				cpu_cnt[pkg_id][die_id]++;
		}
		closedir(dir);
	}
}