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
typedef  int /*<<< orphan*/  umode_t ;
typedef  int u32 ;

/* Variables and functions */
 int MAY_EXEC ; 
 int MAY_READ ; 
 int MAY_WRITE ; 
 int NFS_DIR_MAY_WRITE ; 
 int NFS_FILE_MAY_WRITE ; 
 int NFS_MAY_EXECUTE ; 
 int NFS_MAY_LOOKUP ; 
 int NFS_MAY_READ ; 
 int NFS_MAY_WRITE ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfs_access_calc_mask(u32 access_result, umode_t umode)
{
	int mask = 0;

	if (access_result & NFS_MAY_READ)
		mask |= MAY_READ;
	if (S_ISDIR(umode)) {
		if ((access_result & NFS_DIR_MAY_WRITE) == NFS_DIR_MAY_WRITE)
			mask |= MAY_WRITE;
		if ((access_result & NFS_MAY_LOOKUP) == NFS_MAY_LOOKUP)
			mask |= MAY_EXEC;
	} else if (S_ISREG(umode)) {
		if ((access_result & NFS_FILE_MAY_WRITE) == NFS_FILE_MAY_WRITE)
			mask |= MAY_WRITE;
		if ((access_result & NFS_MAY_EXECUTE) == NFS_MAY_EXECUTE)
			mask |= MAY_EXEC;
	} else if (access_result & NFS_MAY_WRITE)
			mask |= MAY_WRITE;
	return mask;
}