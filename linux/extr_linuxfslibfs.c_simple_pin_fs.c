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
struct file_system_type {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct vfsmount*) ; 
 int PTR_ERR (struct vfsmount*) ; 
 int /*<<< orphan*/  SB_KERNMOUNT ; 
 int /*<<< orphan*/  mntget (struct vfsmount*) ; 
 int /*<<< orphan*/  mntput (struct vfsmount*) ; 
 int /*<<< orphan*/  pin_fs_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 struct vfsmount* vfs_kern_mount (struct file_system_type*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int simple_pin_fs(struct file_system_type *type, struct vfsmount **mount, int *count)
{
	struct vfsmount *mnt = NULL;
	spin_lock(&pin_fs_lock);
	if (unlikely(!*mount)) {
		spin_unlock(&pin_fs_lock);
		mnt = vfs_kern_mount(type, SB_KERNMOUNT, type->name, NULL);
		if (IS_ERR(mnt))
			return PTR_ERR(mnt);
		spin_lock(&pin_fs_lock);
		if (!*mount)
			*mount = mnt;
	}
	mntget(*mount);
	++*count;
	spin_unlock(&pin_fs_lock);
	mntput(mnt);
	return 0;
}