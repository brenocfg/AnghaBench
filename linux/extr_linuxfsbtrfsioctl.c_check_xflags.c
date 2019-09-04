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
 int EOPNOTSUPP ; 
 unsigned int FS_XFLAG_APPEND ; 
 unsigned int FS_XFLAG_IMMUTABLE ; 
 unsigned int FS_XFLAG_NOATIME ; 
 unsigned int FS_XFLAG_NODUMP ; 
 unsigned int FS_XFLAG_SYNC ; 

__attribute__((used)) static int check_xflags(unsigned int flags)
{
	if (flags & ~(FS_XFLAG_APPEND | FS_XFLAG_IMMUTABLE | FS_XFLAG_NOATIME |
		      FS_XFLAG_NODUMP | FS_XFLAG_SYNC))
		return -EOPNOTSUPP;
	return 0;
}