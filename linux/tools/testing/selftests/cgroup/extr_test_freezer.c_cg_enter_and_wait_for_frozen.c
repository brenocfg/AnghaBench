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
 int cg_check_frozen (char const*,int) ; 
 int cg_enter (char const*,int) ; 
 int cg_prepare_for_wait (char const*) ; 
 int cg_wait_for (int) ; 
 int /*<<< orphan*/  close (int) ; 

__attribute__((used)) static int cg_enter_and_wait_for_frozen(const char *cgroup, int pid,
					bool frozen)
{
	int fd, ret = -1;
	int attempts;

	fd = cg_prepare_for_wait(cgroup);
	if (fd < 0)
		return fd;

	ret = cg_enter(cgroup, pid);
	if (ret)
		goto out;

	for (attempts = 0; attempts < 10; attempts++) {
		ret = cg_wait_for(fd);
		if (ret)
			break;

		ret = cg_check_frozen(cgroup, frozen);
		if (ret)
			continue;
	}

out:
	close(fd);
	return ret;
}