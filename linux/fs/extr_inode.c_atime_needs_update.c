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
struct vfsmount {int mnt_flags; } ;
struct timespec64 {int dummy; } ;
struct path {struct vfsmount* mnt; } ;
struct inode {int i_flags; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_mode; TYPE_1__* i_sb; } ;
struct TYPE_2__ {int s_flags; } ;

/* Variables and functions */
 scalar_t__ HAS_UNMAPPED_ID (struct inode*) ; 
 scalar_t__ IS_NOATIME (struct inode*) ; 
 int MNT_NOATIME ; 
 int MNT_NODIRATIME ; 
 int SB_NODIRATIME ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int S_NOATIME ; 
 struct timespec64 current_time (struct inode*) ; 
 int /*<<< orphan*/  relatime_need_update (struct vfsmount*,struct inode*,struct timespec64) ; 
 scalar_t__ timespec64_equal (int /*<<< orphan*/ *,struct timespec64*) ; 

bool atime_needs_update(const struct path *path, struct inode *inode)
{
	struct vfsmount *mnt = path->mnt;
	struct timespec64 now;

	if (inode->i_flags & S_NOATIME)
		return false;

	/* Atime updates will likely cause i_uid and i_gid to be written
	 * back improprely if their true value is unknown to the vfs.
	 */
	if (HAS_UNMAPPED_ID(inode))
		return false;

	if (IS_NOATIME(inode))
		return false;
	if ((inode->i_sb->s_flags & SB_NODIRATIME) && S_ISDIR(inode->i_mode))
		return false;

	if (mnt->mnt_flags & MNT_NOATIME)
		return false;
	if ((mnt->mnt_flags & MNT_NODIRATIME) && S_ISDIR(inode->i_mode))
		return false;

	now = current_time(inode);

	if (!relatime_need_update(mnt, inode, now))
		return false;

	if (timespec64_equal(&inode->i_atime, &now))
		return false;

	return true;
}