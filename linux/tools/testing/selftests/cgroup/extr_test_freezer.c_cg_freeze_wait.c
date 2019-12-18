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
 int cg_freeze_nowait (char const*,int) ; 
 int cg_prepare_for_wait (char const*) ; 
 int cg_wait_for (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  debug (char*) ; 

__attribute__((used)) static int cg_freeze_wait(const char *cgroup, bool freeze)
{
	int fd, ret = -1;

	fd = cg_prepare_for_wait(cgroup);
	if (fd < 0)
		return fd;

	ret = cg_freeze_nowait(cgroup, freeze);
	if (ret) {
		debug("Error: cg_freeze_nowait() failed\n");
		goto out;
	}

	ret = cg_wait_for(fd);
	if (ret)
		goto out;

	ret = cg_check_frozen(cgroup, freeze);
out:
	close(fd);
	return ret;
}