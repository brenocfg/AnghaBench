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
 int FS_APPEND_FL ; 
 int FS_COMPR_FL ; 
 int FS_DIRSYNC_FL ; 
 int FS_IMMUTABLE_FL ; 
 int FS_SYNC_FL ; 
 int UBIFS_APPEND_FL ; 
 int UBIFS_COMPR_FL ; 
 int UBIFS_DIRSYNC_FL ; 
 int UBIFS_IMMUTABLE_FL ; 
 int UBIFS_SYNC_FL ; 

__attribute__((used)) static int ubifs2ioctl(int ubifs_flags)
{
	int ioctl_flags = 0;

	if (ubifs_flags & UBIFS_COMPR_FL)
		ioctl_flags |= FS_COMPR_FL;
	if (ubifs_flags & UBIFS_SYNC_FL)
		ioctl_flags |= FS_SYNC_FL;
	if (ubifs_flags & UBIFS_APPEND_FL)
		ioctl_flags |= FS_APPEND_FL;
	if (ubifs_flags & UBIFS_IMMUTABLE_FL)
		ioctl_flags |= FS_IMMUTABLE_FL;
	if (ubifs_flags & UBIFS_DIRSYNC_FL)
		ioctl_flags |= FS_DIRSYNC_FL;

	return ioctl_flags;
}