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
struct vfsmount {int mnt_flags; } ;
struct mount {int dummy; } ;

/* Variables and functions */
 int MNT_DOOMED ; 
 int MNT_SYNC_UMOUNT ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  lock_mount_hash () ; 
 int /*<<< orphan*/  mnt_add_count (struct mount*,int) ; 
 int /*<<< orphan*/  mount_lock ; 
 scalar_t__ read_seqretry (int /*<<< orphan*/ *,unsigned int) ; 
 struct mount* real_mount (struct vfsmount*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_mount_hash () ; 

int __legitimize_mnt(struct vfsmount *bastard, unsigned seq)
{
	struct mount *mnt;
	if (read_seqretry(&mount_lock, seq))
		return 1;
	if (bastard == NULL)
		return 0;
	mnt = real_mount(bastard);
	mnt_add_count(mnt, 1);
	smp_mb();			// see mntput_no_expire()
	if (likely(!read_seqretry(&mount_lock, seq)))
		return 0;
	if (bastard->mnt_flags & MNT_SYNC_UMOUNT) {
		mnt_add_count(mnt, -1);
		return 1;
	}
	lock_mount_hash();
	if (unlikely(bastard->mnt_flags & MNT_DOOMED)) {
		mnt_add_count(mnt, -1);
		unlock_mount_hash();
		return 1;
	}
	unlock_mount_hash();
	/* caller will mntput() */
	return -1;
}