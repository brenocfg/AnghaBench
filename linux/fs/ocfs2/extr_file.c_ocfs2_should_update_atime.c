#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vfsmount {int mnt_flags; } ;
struct timespec64 {scalar_t__ tv_sec; } ;
struct ocfs2_super {scalar_t__ s_atime_quantum; } ;
struct TYPE_3__ {scalar_t__ tv_sec; } ;
struct inode {int i_flags; TYPE_1__ i_atime; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_mode; TYPE_2__* i_sb; } ;
struct TYPE_4__ {int s_flags; } ;

/* Variables and functions */
 int MNT_NOATIME ; 
 int MNT_NODIRATIME ; 
 int MNT_RELATIME ; 
 struct ocfs2_super* OCFS2_SB (TYPE_2__*) ; 
 int SB_NODIRATIME ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int S_NOATIME ; 
 struct timespec64 current_time (struct inode*) ; 
 scalar_t__ ocfs2_is_hard_readonly (struct ocfs2_super*) ; 
 scalar_t__ ocfs2_is_soft_readonly (struct ocfs2_super*) ; 
 scalar_t__ timespec64_compare (TYPE_1__*,int /*<<< orphan*/ *) ; 

int ocfs2_should_update_atime(struct inode *inode,
			      struct vfsmount *vfsmnt)
{
	struct timespec64 now;
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	if (ocfs2_is_hard_readonly(osb) || ocfs2_is_soft_readonly(osb))
		return 0;

	if ((inode->i_flags & S_NOATIME) ||
	    ((inode->i_sb->s_flags & SB_NODIRATIME) && S_ISDIR(inode->i_mode)))
		return 0;

	/*
	 * We can be called with no vfsmnt structure - NFSD will
	 * sometimes do this.
	 *
	 * Note that our action here is different than touch_atime() -
	 * if we can't tell whether this is a noatime mount, then we
	 * don't know whether to trust the value of s_atime_quantum.
	 */
	if (vfsmnt == NULL)
		return 0;

	if ((vfsmnt->mnt_flags & MNT_NOATIME) ||
	    ((vfsmnt->mnt_flags & MNT_NODIRATIME) && S_ISDIR(inode->i_mode)))
		return 0;

	if (vfsmnt->mnt_flags & MNT_RELATIME) {
		if ((timespec64_compare(&inode->i_atime, &inode->i_mtime) <= 0) ||
		    (timespec64_compare(&inode->i_atime, &inode->i_ctime) <= 0))
			return 1;

		return 0;
	}

	now = current_time(inode);
	if ((now.tv_sec - inode->i_atime.tv_sec <= osb->s_atime_quantum))
		return 0;
	else
		return 1;
}