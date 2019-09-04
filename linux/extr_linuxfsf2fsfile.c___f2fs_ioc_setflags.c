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
struct inode {int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mode; } ;
struct f2fs_inode_info {unsigned int i_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_LINUX_IMMUTABLE ; 
 int EPERM ; 
 unsigned int F2FS_APPEND_FL ; 
 unsigned int F2FS_FL_USER_MODIFIABLE ; 
 struct f2fs_inode_info* F2FS_I (struct inode*) ; 
 unsigned int F2FS_IMMUTABLE_FL ; 
 int F2FS_PROJINHERIT_FL ; 
 int /*<<< orphan*/  FI_PROJ_INHERIT ; 
 scalar_t__ IS_NOQUOTA (struct inode*) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int /*<<< orphan*/  f2fs_mark_inode_dirty_sync (struct inode*,int) ; 
 unsigned int f2fs_mask_flags (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  f2fs_set_inode_flags (struct inode*) ; 
 int /*<<< orphan*/  set_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __f2fs_ioc_setflags(struct inode *inode, unsigned int flags)
{
	struct f2fs_inode_info *fi = F2FS_I(inode);
	unsigned int oldflags;

	/* Is it quota file? Do not allow user to mess with it */
	if (IS_NOQUOTA(inode))
		return -EPERM;

	flags = f2fs_mask_flags(inode->i_mode, flags);

	oldflags = fi->i_flags;

	if ((flags ^ oldflags) & (F2FS_APPEND_FL | F2FS_IMMUTABLE_FL))
		if (!capable(CAP_LINUX_IMMUTABLE))
			return -EPERM;

	flags = flags & F2FS_FL_USER_MODIFIABLE;
	flags |= oldflags & ~F2FS_FL_USER_MODIFIABLE;
	fi->i_flags = flags;

	if (fi->i_flags & F2FS_PROJINHERIT_FL)
		set_inode_flag(inode, FI_PROJ_INHERIT);
	else
		clear_inode_flag(inode, FI_PROJ_INHERIT);

	inode->i_ctime = current_time(inode);
	f2fs_set_inode_flags(inode);
	f2fs_mark_inode_dirty_sync(inode, false);
	return 0;
}