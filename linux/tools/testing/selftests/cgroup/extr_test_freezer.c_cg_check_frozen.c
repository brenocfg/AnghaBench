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
 scalar_t__ cg_read_strstr (char const*,char*,char*) ; 
 int /*<<< orphan*/  debug (char*,char const*) ; 

__attribute__((used)) static int cg_check_frozen(const char *cgroup, bool frozen)
{
	if (frozen) {
		if (cg_read_strstr(cgroup, "cgroup.events", "frozen 1") != 0) {
			debug("Cgroup %s isn't frozen\n", cgroup);
			return -1;
		}
	} else {
		/*
		 * Check the cgroup.events::frozen value.
		 */
		if (cg_read_strstr(cgroup, "cgroup.events", "frozen 0") != 0) {
			debug("Cgroup %s is frozen\n", cgroup);
			return -1;
		}
	}

	return 0;
}