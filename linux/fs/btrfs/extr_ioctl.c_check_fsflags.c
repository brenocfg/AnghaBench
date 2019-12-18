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
 int EINVAL ; 
 int EOPNOTSUPP ; 
 unsigned int FS_APPEND_FL ; 
 unsigned int FS_COMPR_FL ; 
 unsigned int FS_DIRSYNC_FL ; 
 unsigned int FS_IMMUTABLE_FL ; 
 unsigned int FS_NOATIME_FL ; 
 unsigned int FS_NOCOMP_FL ; 
 unsigned int FS_NOCOW_FL ; 
 unsigned int FS_NODUMP_FL ; 
 unsigned int FS_SYNC_FL ; 

__attribute__((used)) static int check_fsflags(unsigned int flags)
{
	if (flags & ~(FS_IMMUTABLE_FL | FS_APPEND_FL | \
		      FS_NOATIME_FL | FS_NODUMP_FL | \
		      FS_SYNC_FL | FS_DIRSYNC_FL | \
		      FS_NOCOMP_FL | FS_COMPR_FL |
		      FS_NOCOW_FL))
		return -EOPNOTSUPP;

	if ((flags & FS_NOCOMP_FL) && (flags & FS_COMPR_FL))
		return -EINVAL;

	return 0;
}