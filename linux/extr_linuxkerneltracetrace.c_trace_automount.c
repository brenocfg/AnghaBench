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
struct vfsmount {int dummy; } ;
struct file_system_type {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct vfsmount*) ; 
 struct file_system_type* get_fs_type (char*) ; 
 int /*<<< orphan*/  mntget (struct vfsmount*) ; 
 int /*<<< orphan*/  put_filesystem (struct file_system_type*) ; 
 struct vfsmount* vfs_submount (struct dentry*,struct file_system_type*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct vfsmount *trace_automount(struct dentry *mntpt, void *ingore)
{
	struct vfsmount *mnt;
	struct file_system_type *type;

	/*
	 * To maintain backward compatibility for tools that mount
	 * debugfs to get to the tracing facility, tracefs is automatically
	 * mounted to the debugfs/tracing directory.
	 */
	type = get_fs_type("tracefs");
	if (!type)
		return NULL;
	mnt = vfs_submount(mntpt, type, "tracefs", NULL);
	put_filesystem(type);
	if (IS_ERR(mnt))
		return NULL;
	mntget(mnt);

	return mnt;
}