#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vfsmount {int dummy; } ;
struct file_system_type {int dummy; } ;
struct dentry {TYPE_1__* d_sb; } ;
struct TYPE_2__ {int /*<<< orphan*/ * s_user_ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPERM ; 
 struct vfsmount* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SB_SUBMOUNT ; 
 int /*<<< orphan*/  init_user_ns ; 
 struct vfsmount* vfs_kern_mount (struct file_system_type*,int /*<<< orphan*/ ,char const*,void*) ; 

struct vfsmount *
vfs_submount(const struct dentry *mountpoint, struct file_system_type *type,
	     const char *name, void *data)
{
	/* Until it is worked out how to pass the user namespace
	 * through from the parent mount to the submount don't support
	 * unprivileged mounts with submounts.
	 */
	if (mountpoint->d_sb->s_user_ns != &init_user_ns)
		return ERR_PTR(-EPERM);

	return vfs_kern_mount(type, SB_SUBMOUNT, name, data);
}