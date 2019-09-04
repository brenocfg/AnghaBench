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
 int /*<<< orphan*/  CGROUP_MOUNT_PATH ; 
 int FTW_DEPTH ; 
 int FTW_MOUNT ; 
 int /*<<< orphan*/  PATH_MAX ; 
 int /*<<< orphan*/  WALK_FD_LIMIT ; 
 int /*<<< orphan*/  format_cgroup_path (char*,char*) ; 
 int /*<<< orphan*/  join_cgroup_from_top (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nftw (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nftwfunc ; 

void cleanup_cgroup_environment(void)
{
	char cgroup_workdir[PATH_MAX + 1];

	format_cgroup_path(cgroup_workdir, "");
	join_cgroup_from_top(CGROUP_MOUNT_PATH);
	nftw(cgroup_workdir, nftwfunc, WALK_FD_LIMIT, FTW_DEPTH | FTW_MOUNT);
}