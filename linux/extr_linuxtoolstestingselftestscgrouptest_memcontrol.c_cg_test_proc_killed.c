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
 scalar_t__ cg_read_strcmp (char const*,char*,char*) ; 
 int /*<<< orphan*/  usleep (int) ; 

__attribute__((used)) static int cg_test_proc_killed(const char *cgroup)
{
	int limit;

	for (limit = 10; limit > 0; limit--) {
		if (cg_read_strcmp(cgroup, "cgroup.procs", "") == 0)
			return 0;

		usleep(100000);
	}
	return -1;
}