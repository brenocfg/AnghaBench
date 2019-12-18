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
 int /*<<< orphan*/  IN_MODIFY ; 
 int /*<<< orphan*/  cg_control (char const*,char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  debug (char*) ; 
 int inotify_add_watch (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int inotify_init1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cg_prepare_for_wait(const char *cgroup)
{
	int fd, ret = -1;

	fd = inotify_init1(0);
	if (fd == -1) {
		debug("Error: inotify_init1() failed\n");
		return fd;
	}

	ret = inotify_add_watch(fd, cg_control(cgroup, "cgroup.events"),
				IN_MODIFY);
	if (ret == -1) {
		debug("Error: inotify_add_watch() failed\n");
		close(fd);
	}

	return fd;
}