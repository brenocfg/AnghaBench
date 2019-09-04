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
typedef  int u64 ;
typedef  int /*<<< orphan*/  ino ;
typedef  int /*<<< orphan*/  fileid ;

/* Variables and functions */
 scalar_t__ enable_ino64 ; 

u64 nfs_compat_user_ino64(u64 fileid)
{
#ifdef CONFIG_COMPAT
	compat_ulong_t ino;
#else	
	unsigned long ino;
#endif

	if (enable_ino64)
		return fileid;
	ino = fileid;
	if (sizeof(ino) < sizeof(fileid))
		ino ^= fileid >> (sizeof(fileid)-sizeof(ino)) * 8;
	return ino;
}