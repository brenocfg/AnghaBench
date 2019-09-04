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
struct kernfs_root {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  apply_cgroup_root_flags (unsigned int) ; 
 int parse_cgroup_root_flags (char*,unsigned int*) ; 

__attribute__((used)) static int cgroup_remount(struct kernfs_root *kf_root, int *flags, char *data)
{
	unsigned int root_flags;
	int ret;

	ret = parse_cgroup_root_flags(data, &root_flags);
	if (ret)
		return ret;

	apply_cgroup_root_flags(root_flags);
	return 0;
}