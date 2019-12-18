#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct super_block {int /*<<< orphan*/  s_user_ns; TYPE_1__* s_op; } ;
struct TYPE_9__ {int mnt_flags; struct super_block* mnt_sb; } ;
struct mount {int /*<<< orphan*/  mnt_list; TYPE_4__ mnt; int /*<<< orphan*/  mnt_expiry_mark; } ;
struct TYPE_10__ {TYPE_3__* fs; } ;
struct TYPE_7__ {TYPE_4__* mnt; } ;
struct TYPE_8__ {TYPE_2__ root; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* umount_begin ) (struct super_block*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EAGAIN ; 
 int EBUSY ; 
 int EINVAL ; 
 int EPERM ; 
 int MNT_DETACH ; 
 int MNT_EXPIRE ; 
 int MNT_FORCE ; 
 int MNT_LOCKED ; 
 int UMOUNT_PROPAGATE ; 
 int UMOUNT_SYNC ; 
 TYPE_5__* current ; 
 int do_umount_root (struct super_block*) ; 
 int /*<<< orphan*/  event ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_mount_hash () ; 
 int mnt_get_count (struct mount*) ; 
 int /*<<< orphan*/  namespace_lock () ; 
 int /*<<< orphan*/  namespace_unlock () ; 
 int /*<<< orphan*/  ns_capable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  propagate_mount_busy (struct mount*,int) ; 
 int security_sb_umount (TYPE_4__*,int) ; 
 int /*<<< orphan*/  shrink_submounts (struct mount*) ; 
 int /*<<< orphan*/  stub1 (struct super_block*) ; 
 int /*<<< orphan*/  umount_tree (struct mount*,int) ; 
 int /*<<< orphan*/  unlock_mount_hash () ; 
 int /*<<< orphan*/  xchg (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int do_umount(struct mount *mnt, int flags)
{
	struct super_block *sb = mnt->mnt.mnt_sb;
	int retval;

	retval = security_sb_umount(&mnt->mnt, flags);
	if (retval)
		return retval;

	/*
	 * Allow userspace to request a mountpoint be expired rather than
	 * unmounting unconditionally. Unmount only happens if:
	 *  (1) the mark is already set (the mark is cleared by mntput())
	 *  (2) the usage count == 1 [parent vfsmount] + 1 [sys_umount]
	 */
	if (flags & MNT_EXPIRE) {
		if (&mnt->mnt == current->fs->root.mnt ||
		    flags & (MNT_FORCE | MNT_DETACH))
			return -EINVAL;

		/*
		 * probably don't strictly need the lock here if we examined
		 * all race cases, but it's a slowpath.
		 */
		lock_mount_hash();
		if (mnt_get_count(mnt) != 2) {
			unlock_mount_hash();
			return -EBUSY;
		}
		unlock_mount_hash();

		if (!xchg(&mnt->mnt_expiry_mark, 1))
			return -EAGAIN;
	}

	/*
	 * If we may have to abort operations to get out of this
	 * mount, and they will themselves hold resources we must
	 * allow the fs to do things. In the Unix tradition of
	 * 'Gee thats tricky lets do it in userspace' the umount_begin
	 * might fail to complete on the first run through as other tasks
	 * must return, and the like. Thats for the mount program to worry
	 * about for the moment.
	 */

	if (flags & MNT_FORCE && sb->s_op->umount_begin) {
		sb->s_op->umount_begin(sb);
	}

	/*
	 * No sense to grab the lock for this test, but test itself looks
	 * somewhat bogus. Suggestions for better replacement?
	 * Ho-hum... In principle, we might treat that as umount + switch
	 * to rootfs. GC would eventually take care of the old vfsmount.
	 * Actually it makes sense, especially if rootfs would contain a
	 * /reboot - static binary that would close all descriptors and
	 * call reboot(9). Then init(8) could umount root and exec /reboot.
	 */
	if (&mnt->mnt == current->fs->root.mnt && !(flags & MNT_DETACH)) {
		/*
		 * Special case for "unmounting" root ...
		 * we just try to remount it readonly.
		 */
		if (!ns_capable(sb->s_user_ns, CAP_SYS_ADMIN))
			return -EPERM;
		return do_umount_root(sb);
	}

	namespace_lock();
	lock_mount_hash();

	/* Recheck MNT_LOCKED with the locks held */
	retval = -EINVAL;
	if (mnt->mnt.mnt_flags & MNT_LOCKED)
		goto out;

	event++;
	if (flags & MNT_DETACH) {
		if (!list_empty(&mnt->mnt_list))
			umount_tree(mnt, UMOUNT_PROPAGATE);
		retval = 0;
	} else {
		shrink_submounts(mnt);
		retval = -EBUSY;
		if (!propagate_mount_busy(mnt, 2)) {
			if (!list_empty(&mnt->mnt_list))
				umount_tree(mnt, UMOUNT_PROPAGATE|UMOUNT_SYNC);
			retval = 0;
		}
	}
out:
	unlock_mount_hash();
	namespace_unlock();
	return retval;
}