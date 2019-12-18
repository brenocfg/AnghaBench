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
struct inode {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 unsigned int FS_DIRSYNC_FL ; 
 unsigned int FS_NOATIME_FL ; 
 unsigned int FS_NODUMP_FL ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int btrfs_mask_fsflags_for_type(struct inode *inode,
		unsigned int flags)
{
	if (S_ISDIR(inode->i_mode))
		return flags;
	else if (S_ISREG(inode->i_mode))
		return flags & ~FS_DIRSYNC_FL;
	else
		return flags & (FS_NODUMP_FL | FS_NOATIME_FL);
}