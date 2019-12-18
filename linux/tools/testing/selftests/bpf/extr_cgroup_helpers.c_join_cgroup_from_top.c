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
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  cgroup_procs_path ;

/* Variables and functions */
 int /*<<< orphan*/  O_WRONLY ; 
 int /*<<< orphan*/  PATH_MAX ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ dprintf (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  log_err (char*,...) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

__attribute__((used)) static int join_cgroup_from_top(char *cgroup_path)
{
	char cgroup_procs_path[PATH_MAX + 1];
	pid_t pid = getpid();
	int fd, rc = 0;

	snprintf(cgroup_procs_path, sizeof(cgroup_procs_path),
		 "%s/cgroup.procs", cgroup_path);

	fd = open(cgroup_procs_path, O_WRONLY);
	if (fd < 0) {
		log_err("Opening Cgroup Procs: %s", cgroup_procs_path);
		return 1;
	}

	if (dprintf(fd, "%d\n", pid) < 0) {
		log_err("Joining Cgroup");
		rc = 1;
	}

	close(fd);
	return rc;
}