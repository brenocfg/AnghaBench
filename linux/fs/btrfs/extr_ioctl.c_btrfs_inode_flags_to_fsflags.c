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

/* Variables and functions */
 unsigned int BTRFS_INODE_APPEND ; 
 unsigned int BTRFS_INODE_COMPRESS ; 
 unsigned int BTRFS_INODE_DIRSYNC ; 
 unsigned int BTRFS_INODE_IMMUTABLE ; 
 unsigned int BTRFS_INODE_NOATIME ; 
 unsigned int BTRFS_INODE_NOCOMPRESS ; 
 unsigned int BTRFS_INODE_NODATACOW ; 
 unsigned int BTRFS_INODE_NODUMP ; 
 unsigned int BTRFS_INODE_SYNC ; 
 unsigned int FS_APPEND_FL ; 
 unsigned int FS_COMPR_FL ; 
 unsigned int FS_DIRSYNC_FL ; 
 unsigned int FS_IMMUTABLE_FL ; 
 unsigned int FS_NOATIME_FL ; 
 unsigned int FS_NOCOMP_FL ; 
 unsigned int FS_NOCOW_FL ; 
 unsigned int FS_NODUMP_FL ; 
 unsigned int FS_SYNC_FL ; 

__attribute__((used)) static unsigned int btrfs_inode_flags_to_fsflags(unsigned int flags)
{
	unsigned int iflags = 0;

	if (flags & BTRFS_INODE_SYNC)
		iflags |= FS_SYNC_FL;
	if (flags & BTRFS_INODE_IMMUTABLE)
		iflags |= FS_IMMUTABLE_FL;
	if (flags & BTRFS_INODE_APPEND)
		iflags |= FS_APPEND_FL;
	if (flags & BTRFS_INODE_NODUMP)
		iflags |= FS_NODUMP_FL;
	if (flags & BTRFS_INODE_NOATIME)
		iflags |= FS_NOATIME_FL;
	if (flags & BTRFS_INODE_DIRSYNC)
		iflags |= FS_DIRSYNC_FL;
	if (flags & BTRFS_INODE_NODATACOW)
		iflags |= FS_NOCOW_FL;

	if (flags & BTRFS_INODE_NOCOMPRESS)
		iflags |= FS_NOCOMP_FL;
	else if (flags & BTRFS_INODE_COMPRESS)
		iflags |= FS_COMPR_FL;

	return iflags;
}