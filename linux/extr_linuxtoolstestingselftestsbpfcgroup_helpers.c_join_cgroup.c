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
 int /*<<< orphan*/  PATH_MAX ; 
 int /*<<< orphan*/  format_cgroup_path (char*,char const*) ; 
 int join_cgroup_from_top (char*) ; 

int join_cgroup(const char *path)
{
	char cgroup_path[PATH_MAX + 1];

	format_cgroup_path(cgroup_path, path);
	return join_cgroup_from_top(cgroup_path);
}