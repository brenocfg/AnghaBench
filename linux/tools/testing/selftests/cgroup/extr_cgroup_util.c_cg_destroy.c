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
 scalar_t__ EBUSY ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  cg_killall (char const*) ; 
 scalar_t__ errno ; 
 int rmdir (char const*) ; 
 int /*<<< orphan*/  usleep (int) ; 

int cg_destroy(const char *cgroup)
{
	int ret;

retry:
	ret = rmdir(cgroup);
	if (ret && errno == EBUSY) {
		cg_killall(cgroup);
		usleep(100);
		goto retry;
	}

	if (ret && errno == ENOENT)
		ret = 0;

	return ret;
}