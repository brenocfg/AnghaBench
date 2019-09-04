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
struct inode {int dummy; } ;
struct TYPE_2__ {unsigned int mode2; } ;

/* Variables and functions */
 unsigned int JFS_APPEND_FL ; 
 unsigned int JFS_DIRSYNC_FL ; 
 unsigned int JFS_IMMUTABLE_FL ; 
 TYPE_1__* JFS_IP (struct inode*) ; 
 unsigned int JFS_NOATIME_FL ; 
 unsigned int JFS_SYNC_FL ; 
 unsigned int S_APPEND ; 
 unsigned int S_DIRSYNC ; 
 unsigned int S_IMMUTABLE ; 
 unsigned int S_NOATIME ; 
 unsigned int S_SYNC ; 
 int /*<<< orphan*/  inode_set_flags (struct inode*,unsigned int,unsigned int) ; 

void jfs_set_inode_flags(struct inode *inode)
{
	unsigned int flags = JFS_IP(inode)->mode2;
	unsigned int new_fl = 0;

	if (flags & JFS_IMMUTABLE_FL)
		new_fl |= S_IMMUTABLE;
	if (flags & JFS_APPEND_FL)
		new_fl |= S_APPEND;
	if (flags & JFS_NOATIME_FL)
		new_fl |= S_NOATIME;
	if (flags & JFS_DIRSYNC_FL)
		new_fl |= S_DIRSYNC;
	if (flags & JFS_SYNC_FL)
		new_fl |= S_SYNC;
	inode_set_flags(inode, new_fl, S_IMMUTABLE | S_APPEND | S_NOATIME |
			S_DIRSYNC | S_SYNC);
}