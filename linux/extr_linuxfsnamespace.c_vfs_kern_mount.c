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
struct vfsmount {struct dentry* mnt_root; TYPE_1__* mnt_sb; int /*<<< orphan*/  mnt_flags; } ;
struct mount {struct vfsmount mnt; int /*<<< orphan*/  mnt_instance; struct mount* mnt_parent; struct dentry* mnt_mountpoint; } ;
struct file_system_type {int dummy; } ;
struct dentry {TYPE_1__* d_sb; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_mounts; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct vfsmount* ERR_CAST (struct dentry*) ; 
 struct vfsmount* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  MNT_INTERNAL ; 
 int SB_KERNMOUNT ; 
 struct mount* alloc_vfsmnt (char const*) ; 
 int /*<<< orphan*/  free_vfsmnt (struct mount*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_mount_hash () ; 
 int /*<<< orphan*/  mnt_free_id (struct mount*) ; 
 struct dentry* mount_fs (struct file_system_type*,int,char const*,void*) ; 
 int /*<<< orphan*/  unlock_mount_hash () ; 

struct vfsmount *
vfs_kern_mount(struct file_system_type *type, int flags, const char *name, void *data)
{
	struct mount *mnt;
	struct dentry *root;

	if (!type)
		return ERR_PTR(-ENODEV);

	mnt = alloc_vfsmnt(name);
	if (!mnt)
		return ERR_PTR(-ENOMEM);

	if (flags & SB_KERNMOUNT)
		mnt->mnt.mnt_flags = MNT_INTERNAL;

	root = mount_fs(type, flags, name, data);
	if (IS_ERR(root)) {
		mnt_free_id(mnt);
		free_vfsmnt(mnt);
		return ERR_CAST(root);
	}

	mnt->mnt.mnt_root = root;
	mnt->mnt.mnt_sb = root->d_sb;
	mnt->mnt_mountpoint = mnt->mnt.mnt_root;
	mnt->mnt_parent = mnt;
	lock_mount_hash();
	list_add_tail(&mnt->mnt_instance, &root->d_sb->s_mounts);
	unlock_mount_hash();
	return &mnt->mnt;
}