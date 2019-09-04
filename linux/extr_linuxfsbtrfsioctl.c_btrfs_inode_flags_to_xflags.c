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
 unsigned int BTRFS_INODE_IMMUTABLE ; 
 unsigned int BTRFS_INODE_NOATIME ; 
 unsigned int BTRFS_INODE_NODUMP ; 
 unsigned int BTRFS_INODE_SYNC ; 
 unsigned int FS_XFLAG_APPEND ; 
 unsigned int FS_XFLAG_IMMUTABLE ; 
 unsigned int FS_XFLAG_NOATIME ; 
 unsigned int FS_XFLAG_NODUMP ; 
 unsigned int FS_XFLAG_SYNC ; 

__attribute__((used)) static unsigned int btrfs_inode_flags_to_xflags(unsigned int flags)
{
	unsigned int xflags = 0;

	if (flags & BTRFS_INODE_APPEND)
		xflags |= FS_XFLAG_APPEND;
	if (flags & BTRFS_INODE_IMMUTABLE)
		xflags |= FS_XFLAG_IMMUTABLE;
	if (flags & BTRFS_INODE_NOATIME)
		xflags |= FS_XFLAG_NOATIME;
	if (flags & BTRFS_INODE_NODUMP)
		xflags |= FS_XFLAG_NODUMP;
	if (flags & BTRFS_INODE_SYNC)
		xflags |= FS_XFLAG_SYNC;

	return xflags;
}