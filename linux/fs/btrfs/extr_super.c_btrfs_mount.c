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
typedef  int /*<<< orphan*/  u64 ;
struct vfsmount {TYPE_1__* mnt_sb; } ;
struct file_system_type {int dummy; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_umount; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 struct dentry* ERR_CAST (struct vfsmount*) ; 
 struct dentry* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct vfsmount*) ; 
 int /*<<< orphan*/  PTR_ERR_OR_ZERO (struct vfsmount*) ; 
 int SB_RDONLY ; 
 int btrfs_parse_subvol_options (void*,char**,int /*<<< orphan*/ *) ; 
 int btrfs_remount (TYPE_1__*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_root_fs_type ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  mntput (struct vfsmount*) ; 
 struct dentry* mount_subvol (char*,int /*<<< orphan*/ ,struct vfsmount*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 struct vfsmount* vfs_kern_mount (int /*<<< orphan*/ *,int,char const*,void*) ; 

__attribute__((used)) static struct dentry *btrfs_mount(struct file_system_type *fs_type, int flags,
		const char *device_name, void *data)
{
	struct vfsmount *mnt_root;
	struct dentry *root;
	char *subvol_name = NULL;
	u64 subvol_objectid = 0;
	int error = 0;

	error = btrfs_parse_subvol_options(data, &subvol_name,
					&subvol_objectid);
	if (error) {
		kfree(subvol_name);
		return ERR_PTR(error);
	}

	/* mount device's root (/) */
	mnt_root = vfs_kern_mount(&btrfs_root_fs_type, flags, device_name, data);
	if (PTR_ERR_OR_ZERO(mnt_root) == -EBUSY) {
		if (flags & SB_RDONLY) {
			mnt_root = vfs_kern_mount(&btrfs_root_fs_type,
				flags & ~SB_RDONLY, device_name, data);
		} else {
			mnt_root = vfs_kern_mount(&btrfs_root_fs_type,
				flags | SB_RDONLY, device_name, data);
			if (IS_ERR(mnt_root)) {
				root = ERR_CAST(mnt_root);
				kfree(subvol_name);
				goto out;
			}

			down_write(&mnt_root->mnt_sb->s_umount);
			error = btrfs_remount(mnt_root->mnt_sb, &flags, NULL);
			up_write(&mnt_root->mnt_sb->s_umount);
			if (error < 0) {
				root = ERR_PTR(error);
				mntput(mnt_root);
				kfree(subvol_name);
				goto out;
			}
		}
	}
	if (IS_ERR(mnt_root)) {
		root = ERR_CAST(mnt_root);
		kfree(subvol_name);
		goto out;
	}

	/* mount_subvol() will free subvol_name and mnt_root */
	root = mount_subvol(subvol_name, subvol_objectid, mnt_root);

out:
	return root;
}