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
struct TYPE_2__ {unsigned int i_flags; } ;

/* Variables and functions */
 unsigned int F2FS_APPEND_FL ; 
 unsigned int F2FS_CASEFOLD_FL ; 
 unsigned int F2FS_DIRSYNC_FL ; 
 TYPE_1__* F2FS_I (struct inode*) ; 
 unsigned int F2FS_IMMUTABLE_FL ; 
 unsigned int F2FS_NOATIME_FL ; 
 unsigned int F2FS_SYNC_FL ; 
 unsigned int S_APPEND ; 
 unsigned int S_CASEFOLD ; 
 unsigned int S_DIRSYNC ; 
 unsigned int S_ENCRYPTED ; 
 unsigned int S_IMMUTABLE ; 
 unsigned int S_NOATIME ; 
 unsigned int S_SYNC ; 
 unsigned int S_VERITY ; 
 scalar_t__ file_is_encrypt (struct inode*) ; 
 scalar_t__ file_is_verity (struct inode*) ; 
 int /*<<< orphan*/  inode_set_flags (struct inode*,unsigned int,unsigned int) ; 

void f2fs_set_inode_flags(struct inode *inode)
{
	unsigned int flags = F2FS_I(inode)->i_flags;
	unsigned int new_fl = 0;

	if (flags & F2FS_SYNC_FL)
		new_fl |= S_SYNC;
	if (flags & F2FS_APPEND_FL)
		new_fl |= S_APPEND;
	if (flags & F2FS_IMMUTABLE_FL)
		new_fl |= S_IMMUTABLE;
	if (flags & F2FS_NOATIME_FL)
		new_fl |= S_NOATIME;
	if (flags & F2FS_DIRSYNC_FL)
		new_fl |= S_DIRSYNC;
	if (file_is_encrypt(inode))
		new_fl |= S_ENCRYPTED;
	if (file_is_verity(inode))
		new_fl |= S_VERITY;
	if (flags & F2FS_CASEFOLD_FL)
		new_fl |= S_CASEFOLD;
	inode_set_flags(inode, new_fl,
			S_SYNC|S_APPEND|S_IMMUTABLE|S_NOATIME|S_DIRSYNC|
			S_ENCRYPTED|S_VERITY|S_CASEFOLD);
}