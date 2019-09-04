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

/* Variables and functions */
 unsigned int MAX_PACKAGES ; 
 int /*<<< orphan*/  errx (int,char*,int,unsigned int,unsigned int) ; 
 int* first_cpu_in_pkg ; 
 unsigned int get_pkg_num (int) ; 
 int max_cpu_num ; 
 unsigned int max_pkg_num ; 
 unsigned long long pkg_present_set ; 

int set_max_cpu_pkg_num(int cpu)
{
	unsigned int pkg;

	if (max_cpu_num < cpu)
		max_cpu_num = cpu;

	pkg = get_pkg_num(cpu);

	if (pkg >= MAX_PACKAGES)
		errx(1, "cpu%d: %d >= MAX_PACKAGES (%d)", cpu, pkg, MAX_PACKAGES);

	if (pkg > max_pkg_num)
		max_pkg_num = pkg;

	if ((pkg_present_set & (1ULL << pkg)) == 0) {
		pkg_present_set |= (1ULL << pkg);
		first_cpu_in_pkg[pkg] = cpu;
	}

	return 0;
}