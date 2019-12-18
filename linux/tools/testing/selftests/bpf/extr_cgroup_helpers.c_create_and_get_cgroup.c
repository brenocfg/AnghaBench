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
 scalar_t__ EEXIST ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  PATH_MAX ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  format_cgroup_path (char*,char const*) ; 
 int /*<<< orphan*/  log_err (char*,...) ; 
 scalar_t__ mkdir (char*,int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 

int create_and_get_cgroup(const char *path)
{
	char cgroup_path[PATH_MAX + 1];
	int fd;

	format_cgroup_path(cgroup_path, path);
	if (mkdir(cgroup_path, 0777) && errno != EEXIST) {
		log_err("mkdiring cgroup %s .. %s", path, cgroup_path);
		return -1;
	}

	fd = open(cgroup_path, O_RDONLY);
	if (fd < 0) {
		log_err("Opening Cgroup");
		return -1;
	}

	return fd;
}