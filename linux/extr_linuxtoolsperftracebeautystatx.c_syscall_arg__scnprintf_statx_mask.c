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
struct syscall_arg {int val; } ;

/* Variables and functions */
 int STATX_ATIME ; 
 int STATX_BLOCKS ; 
 int STATX_BTIME ; 
 int STATX_CTIME ; 
 int STATX_GID ; 
 int STATX_INO ; 
 int STATX_MODE ; 
 int STATX_MTIME ; 
 int STATX_NLINK ; 
 int STATX_SIZE ; 
 int STATX_TYPE ; 
 int STATX_UID ; 
 scalar_t__ scnprintf (char*,size_t,char*,char*,...) ; 

size_t syscall_arg__scnprintf_statx_mask(char *bf, size_t size, struct syscall_arg *arg)
{
	int printed = 0, flags = arg->val;

#define	P_FLAG(n) \
	if (flags & STATX_##n) { \
		printed += scnprintf(bf + printed, size - printed, "%s%s", printed ? "|" : "", #n); \
		flags &= ~STATX_##n; \
	}

	P_FLAG(TYPE);
	P_FLAG(MODE);
	P_FLAG(NLINK);
	P_FLAG(UID);
	P_FLAG(GID);
	P_FLAG(ATIME);
	P_FLAG(MTIME);
	P_FLAG(CTIME);
	P_FLAG(INO);
	P_FLAG(SIZE);
	P_FLAG(BLOCKS);
	P_FLAG(BTIME);

#undef P_FLAG

	if (flags)
		printed += scnprintf(bf + printed, size - printed, "%s%#x", printed ? "|" : "", flags);

	return printed;
}