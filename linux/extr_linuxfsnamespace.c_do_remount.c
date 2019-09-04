#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct super_block {int /*<<< orphan*/  s_umount; int /*<<< orphan*/  s_user_ns; } ;
struct path {scalar_t__ dentry; TYPE_2__* mnt; } ;
struct TYPE_4__ {int mnt_flags; } ;
struct mount {int /*<<< orphan*/  mnt_ns; TYPE_1__ mnt; } ;
struct TYPE_5__ {scalar_t__ mnt_root; struct super_block* mnt_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EINVAL ; 
 int EPERM ; 
 int MNT_ATIME_MASK ; 
 int MNT_LOCK_ATIME ; 
 int MNT_LOCK_NODEV ; 
 int MNT_LOCK_NOEXEC ; 
 int MNT_LOCK_NOSUID ; 
 int MNT_LOCK_READONLY ; 
 int MNT_NODEV ; 
 int MNT_NOEXEC ; 
 int MNT_NOSUID ; 
 int MNT_READONLY ; 
 int MNT_USER_SETTABLE_MASK ; 
 int MS_BIND ; 
 int change_mount_flags (TYPE_2__*,int) ; 
 int /*<<< orphan*/  check_mnt (struct mount*) ; 
 int do_remount_sb (struct super_block*,int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_mount_hash () ; 
 int /*<<< orphan*/  ns_capable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mount* real_mount (TYPE_2__*) ; 
 int security_sb_remount (struct super_block*,void*) ; 
 int /*<<< orphan*/  touch_mnt_namespace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_mount_hash () ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int do_remount(struct path *path, int ms_flags, int sb_flags,
		      int mnt_flags, void *data)
{
	int err;
	struct super_block *sb = path->mnt->mnt_sb;
	struct mount *mnt = real_mount(path->mnt);

	if (!check_mnt(mnt))
		return -EINVAL;

	if (path->dentry != path->mnt->mnt_root)
		return -EINVAL;

	/* Don't allow changing of locked mnt flags.
	 *
	 * No locks need to be held here while testing the various
	 * MNT_LOCK flags because those flags can never be cleared
	 * once they are set.
	 */
	if ((mnt->mnt.mnt_flags & MNT_LOCK_READONLY) &&
	    !(mnt_flags & MNT_READONLY)) {
		return -EPERM;
	}
	if ((mnt->mnt.mnt_flags & MNT_LOCK_NODEV) &&
	    !(mnt_flags & MNT_NODEV)) {
		return -EPERM;
	}
	if ((mnt->mnt.mnt_flags & MNT_LOCK_NOSUID) &&
	    !(mnt_flags & MNT_NOSUID)) {
		return -EPERM;
	}
	if ((mnt->mnt.mnt_flags & MNT_LOCK_NOEXEC) &&
	    !(mnt_flags & MNT_NOEXEC)) {
		return -EPERM;
	}
	if ((mnt->mnt.mnt_flags & MNT_LOCK_ATIME) &&
	    ((mnt->mnt.mnt_flags & MNT_ATIME_MASK) != (mnt_flags & MNT_ATIME_MASK))) {
		return -EPERM;
	}

	err = security_sb_remount(sb, data);
	if (err)
		return err;

	down_write(&sb->s_umount);
	if (ms_flags & MS_BIND)
		err = change_mount_flags(path->mnt, ms_flags);
	else if (!ns_capable(sb->s_user_ns, CAP_SYS_ADMIN))
		err = -EPERM;
	else
		err = do_remount_sb(sb, sb_flags, data, 0);
	if (!err) {
		lock_mount_hash();
		mnt_flags |= mnt->mnt.mnt_flags & ~MNT_USER_SETTABLE_MASK;
		mnt->mnt.mnt_flags = mnt_flags;
		touch_mnt_namespace(mnt->mnt_ns);
		unlock_mount_hash();
	}
	up_write(&sb->s_umount);
	return err;
}