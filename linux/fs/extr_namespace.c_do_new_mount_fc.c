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
struct super_block {int /*<<< orphan*/  s_umount; } ;
struct path {int dummy; } ;
struct fs_context {TYPE_1__* root; } ;
struct TYPE_2__ {struct super_block* d_sb; } ;

/* Variables and functions */
 int EPERM ; 
 scalar_t__ IS_ERR (struct vfsmount*) ; 
 int PTR_ERR (struct vfsmount*) ; 
 int do_add_mount (int /*<<< orphan*/ ,struct path*,unsigned int) ; 
 int /*<<< orphan*/  fc_drop_locked (struct fs_context*) ; 
 int /*<<< orphan*/  mnt_warn_timestamp_expiry (struct path*,struct vfsmount*) ; 
 int /*<<< orphan*/  mntput (struct vfsmount*) ; 
 scalar_t__ mount_too_revealing (struct super_block*,unsigned int*) ; 
 int /*<<< orphan*/  real_mount (struct vfsmount*) ; 
 int security_sb_kern_mount (struct super_block*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 struct vfsmount* vfs_create_mount (struct fs_context*) ; 

__attribute__((used)) static int do_new_mount_fc(struct fs_context *fc, struct path *mountpoint,
			   unsigned int mnt_flags)
{
	struct vfsmount *mnt;
	struct super_block *sb = fc->root->d_sb;
	int error;

	error = security_sb_kern_mount(sb);
	if (!error && mount_too_revealing(sb, &mnt_flags))
		error = -EPERM;

	if (unlikely(error)) {
		fc_drop_locked(fc);
		return error;
	}

	up_write(&sb->s_umount);

	mnt = vfs_create_mount(fc);
	if (IS_ERR(mnt))
		return PTR_ERR(mnt);

	error = do_add_mount(real_mount(mnt), mountpoint, mnt_flags);
	if (error < 0) {
		mntput(mnt);
		return error;
	}

	mnt_warn_timestamp_expiry(mountpoint, mnt);

	return error;
}