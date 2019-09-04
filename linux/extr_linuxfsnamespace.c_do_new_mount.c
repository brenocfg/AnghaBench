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
struct vfsmount {TYPE_1__* mnt_sb; } ;
struct path {int dummy; } ;
struct file_system_type {int fs_flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_subtype; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int EPERM ; 
 int FS_HAS_SUBTYPE ; 
 scalar_t__ IS_ERR (struct vfsmount*) ; 
 int PTR_ERR (struct vfsmount*) ; 
 int do_add_mount (int /*<<< orphan*/ ,struct path*,int) ; 
 struct vfsmount* fs_set_subtype (struct vfsmount*,char const*) ; 
 struct file_system_type* get_fs_type (char const*) ; 
 int /*<<< orphan*/  mntput (struct vfsmount*) ; 
 scalar_t__ mount_too_revealing (struct vfsmount*,int*) ; 
 int /*<<< orphan*/  put_filesystem (struct file_system_type*) ; 
 int /*<<< orphan*/  real_mount (struct vfsmount*) ; 
 struct vfsmount* vfs_kern_mount (struct file_system_type*,int,char const*,void*) ; 

__attribute__((used)) static int do_new_mount(struct path *path, const char *fstype, int sb_flags,
			int mnt_flags, const char *name, void *data)
{
	struct file_system_type *type;
	struct vfsmount *mnt;
	int err;

	if (!fstype)
		return -EINVAL;

	type = get_fs_type(fstype);
	if (!type)
		return -ENODEV;

	mnt = vfs_kern_mount(type, sb_flags, name, data);
	if (!IS_ERR(mnt) && (type->fs_flags & FS_HAS_SUBTYPE) &&
	    !mnt->mnt_sb->s_subtype)
		mnt = fs_set_subtype(mnt, fstype);

	put_filesystem(type);
	if (IS_ERR(mnt))
		return PTR_ERR(mnt);

	if (mount_too_revealing(mnt, &mnt_flags)) {
		mntput(mnt);
		return -EPERM;
	}

	err = do_add_mount(real_mount(mnt), path, mnt_flags);
	if (err)
		mntput(mnt);
	return err;
}