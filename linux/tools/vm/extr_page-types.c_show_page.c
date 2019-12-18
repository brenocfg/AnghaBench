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
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 scalar_t__ opt_file ; 
 scalar_t__ opt_list_cgroup ; 
 scalar_t__ opt_list_mapcnt ; 
 scalar_t__ opt_pid ; 
 int /*<<< orphan*/  page_flag_name (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,unsigned long,...) ; 

__attribute__((used)) static void show_page(unsigned long voffset, unsigned long offset,
		      uint64_t flags, uint64_t cgroup, uint64_t mapcnt)
{
	if (opt_pid)
		printf("%lx\t", voffset);
	if (opt_file)
		printf("%lu\t", voffset);
	if (opt_list_cgroup)
		printf("@%llu\t", (unsigned long long)cgroup);
	if (opt_list_mapcnt)
		printf("%lu\t", mapcnt);

	printf("%lx\t%s\n", offset, page_flag_name(flags));
}