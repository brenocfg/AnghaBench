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
struct super_block {int /*<<< orphan*/  s_umount; int /*<<< orphan*/  s_user_ns; } ;
struct path {scalar_t__ dentry; TYPE_1__* mnt; } ;
struct mount {int /*<<< orphan*/  mnt; } ;
struct fs_context {int dummy; } ;
struct TYPE_2__ {scalar_t__ mnt_root; struct super_block* mnt_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EINVAL ; 
 int EPERM ; 
 scalar_t__ IS_ERR (struct fs_context*) ; 
 int /*<<< orphan*/  MS_RMT_MASK ; 
 int PTR_ERR (struct fs_context*) ; 
 int /*<<< orphan*/  can_change_locked_flags (struct mount*,int) ; 
 int /*<<< orphan*/  check_mnt (struct mount*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 struct fs_context* fs_context_for_reconfigure (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mnt_warn_timestamp_expiry (struct path*,int /*<<< orphan*/ *) ; 
 scalar_t__ ns_capable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int parse_monolithic_mount_data (struct fs_context*,void*) ; 
 int /*<<< orphan*/  put_fs_context (struct fs_context*) ; 
 struct mount* real_mount (TYPE_1__*) ; 
 int reconfigure_super (struct fs_context*) ; 
 int /*<<< orphan*/  set_mount_attributes (struct mount*,int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int do_remount(struct path *path, int ms_flags, int sb_flags,
		      int mnt_flags, void *data)
{
	int err;
	struct super_block *sb = path->mnt->mnt_sb;
	struct mount *mnt = real_mount(path->mnt);
	struct fs_context *fc;

	if (!check_mnt(mnt))
		return -EINVAL;

	if (path->dentry != path->mnt->mnt_root)
		return -EINVAL;

	if (!can_change_locked_flags(mnt, mnt_flags))
		return -EPERM;

	fc = fs_context_for_reconfigure(path->dentry, sb_flags, MS_RMT_MASK);
	if (IS_ERR(fc))
		return PTR_ERR(fc);

	err = parse_monolithic_mount_data(fc, data);
	if (!err) {
		down_write(&sb->s_umount);
		err = -EPERM;
		if (ns_capable(sb->s_user_ns, CAP_SYS_ADMIN)) {
			err = reconfigure_super(fc);
			if (!err)
				set_mount_attributes(mnt, mnt_flags);
		}
		up_write(&sb->s_umount);
	}

	mnt_warn_timestamp_expiry(path, &mnt->mnt);

	put_fs_context(fc);
	return err;
}