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
 char* CGROUP_MOUNT_PATH ; 
 int /*<<< orphan*/  CLONE_NEWNS ; 
 scalar_t__ EBUSY ; 
 scalar_t__ EEXIST ; 
 int MS_PRIVATE ; 
 int MS_REC ; 
 int /*<<< orphan*/  PATH_MAX ; 
 int /*<<< orphan*/  cleanup_cgroup_environment () ; 
 scalar_t__ enable_all_controllers (char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  format_cgroup_path (char*,char*) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 scalar_t__ mkdir (char*,int) ; 
 scalar_t__ mount (char*,char*,char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ unshare (int /*<<< orphan*/ ) ; 

int setup_cgroup_environment(void)
{
	char cgroup_workdir[PATH_MAX + 1];

	format_cgroup_path(cgroup_workdir, "");

	if (unshare(CLONE_NEWNS)) {
		log_err("unshare");
		return 1;
	}

	if (mount("none", "/", NULL, MS_REC | MS_PRIVATE, NULL)) {
		log_err("mount fakeroot");
		return 1;
	}

	if (mount("none", CGROUP_MOUNT_PATH, "cgroup2", 0, NULL) && errno != EBUSY) {
		log_err("mount cgroup2");
		return 1;
	}

	/* Cleanup existing failed runs, now that the environment is setup */
	cleanup_cgroup_environment();

	if (mkdir(cgroup_workdir, 0777) && errno != EEXIST) {
		log_err("mkdir cgroup work dir");
		return 1;
	}

	if (enable_all_controllers(cgroup_workdir))
		return 1;

	return 0;
}