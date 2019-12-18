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
struct vfsmount {int dummy; } ;
struct timespec64 {int dummy; } ;
struct path {int /*<<< orphan*/  dentry; struct vfsmount* mnt; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_ATIME ; 
 int /*<<< orphan*/  __mnt_drop_write (struct vfsmount*) ; 
 scalar_t__ __mnt_want_write (struct vfsmount*) ; 
 int /*<<< orphan*/  atime_needs_update (struct path const*,struct inode*) ; 
 struct timespec64 current_time (struct inode*) ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_end_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_start_write_trylock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_time (struct inode*,struct timespec64*,int /*<<< orphan*/ ) ; 

void touch_atime(const struct path *path)
{
	struct vfsmount *mnt = path->mnt;
	struct inode *inode = d_inode(path->dentry);
	struct timespec64 now;

	if (!atime_needs_update(path, inode))
		return;

	if (!sb_start_write_trylock(inode->i_sb))
		return;

	if (__mnt_want_write(mnt) != 0)
		goto skip_update;
	/*
	 * File systems can error out when updating inodes if they need to
	 * allocate new space to modify an inode (such is the case for
	 * Btrfs), but since we touch atime while walking down the path we
	 * really don't care if we failed to update the atime of the file,
	 * so just ignore the return value.
	 * We may also fail on filesystems that have the ability to make parts
	 * of the fs read only, e.g. subvolumes in Btrfs.
	 */
	now = current_time(inode);
	update_time(inode, &now, S_ATIME);
	__mnt_drop_write(mnt);
skip_update:
	sb_end_write(inode->i_sb);
}