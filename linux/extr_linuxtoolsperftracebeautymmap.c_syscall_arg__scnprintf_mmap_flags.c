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
struct syscall_arg {int val; int mask; } ;

/* Variables and functions */
 int MAP_ANONYMOUS ; 
 int MAP_DENYWRITE ; 
 int MAP_EXECUTABLE ; 
 int MAP_FILE ; 
 int MAP_FIXED ; 
 int MAP_GROWSDOWN ; 
 int MAP_HUGETLB ; 
 int MAP_LOCKED ; 
 int MAP_NONBLOCK ; 
 int MAP_NORESERVE ; 
 int MAP_POPULATE ; 
 int MAP_PRIVATE ; 
 int MAP_SHARED ; 
 int MAP_STACK ; 
 int MAP_UNINITIALIZED ; 
 scalar_t__ scnprintf (char*,size_t,char*,char*,...) ; 

__attribute__((used)) static size_t syscall_arg__scnprintf_mmap_flags(char *bf, size_t size,
						struct syscall_arg *arg)
{
	int printed = 0, flags = arg->val;

	if (flags & MAP_ANONYMOUS)
		arg->mask |= (1 << 4) | (1 << 5); /* Mask 4th ('fd') and 5th ('offset') args, ignored */

#define	P_MMAP_FLAG(n) \
	if (flags & MAP_##n) { \
		printed += scnprintf(bf + printed, size - printed, "%s%s", printed ? "|" : "", #n); \
		flags &= ~MAP_##n; \
	}

	P_MMAP_FLAG(SHARED);
	P_MMAP_FLAG(PRIVATE);
#ifdef MAP_32BIT
	P_MMAP_FLAG(32BIT);
#endif
	P_MMAP_FLAG(ANONYMOUS);
	P_MMAP_FLAG(DENYWRITE);
	P_MMAP_FLAG(EXECUTABLE);
	P_MMAP_FLAG(FILE);
	P_MMAP_FLAG(FIXED);
#ifdef MAP_FIXED_NOREPLACE
	P_MMAP_FLAG(FIXED_NOREPLACE);
#endif
	P_MMAP_FLAG(GROWSDOWN);
	P_MMAP_FLAG(HUGETLB);
	P_MMAP_FLAG(LOCKED);
	P_MMAP_FLAG(NONBLOCK);
	P_MMAP_FLAG(NORESERVE);
	P_MMAP_FLAG(POPULATE);
	P_MMAP_FLAG(STACK);
	P_MMAP_FLAG(UNINITIALIZED);
#ifdef MAP_SYNC
	P_MMAP_FLAG(SYNC);
#endif
#undef P_MMAP_FLAG

	if (flags)
		printed += scnprintf(bf + printed, size - printed, "%s%#x", printed ? "|" : "", flags);

	return printed;
}