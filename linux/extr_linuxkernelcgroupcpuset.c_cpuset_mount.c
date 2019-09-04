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
struct file_system_type {struct dentry* (* mount ) (struct file_system_type*,int,char const*,char*) ;} ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct file_system_type* get_fs_type (char*) ; 
 int /*<<< orphan*/  put_filesystem (struct file_system_type*) ; 
 struct dentry* stub1 (struct file_system_type*,int,char const*,char*) ; 

__attribute__((used)) static struct dentry *cpuset_mount(struct file_system_type *fs_type,
			 int flags, const char *unused_dev_name, void *data)
{
	struct file_system_type *cgroup_fs = get_fs_type("cgroup");
	struct dentry *ret = ERR_PTR(-ENODEV);
	if (cgroup_fs) {
		char mountopts[] =
			"cpuset,noprefix,"
			"release_agent=/sbin/cpuset_release_agent";
		ret = cgroup_fs->mount(cgroup_fs, flags,
					   unused_dev_name, mountopts);
		put_filesystem(cgroup_fs);
	}
	return ret;
}