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
 int MREMAP_FIXED ; 
 int MREMAP_MAYMOVE ; 
 scalar_t__ scnprintf (char*,size_t,char*,char*,...) ; 

__attribute__((used)) static size_t syscall_arg__scnprintf_mremap_flags(char *bf, size_t size,
						  struct syscall_arg *arg)
{
	int printed = 0, flags = arg->val;

#define P_MREMAP_FLAG(n) \
	if (flags & MREMAP_##n) { \
		printed += scnprintf(bf + printed, size - printed, "%s%s", printed ? "|" : "", #n); \
		flags &= ~MREMAP_##n; \
	}

	P_MREMAP_FLAG(MAYMOVE);
	P_MREMAP_FLAG(FIXED);
#undef P_MREMAP_FLAG

	if (flags)
		printed += scnprintf(bf + printed, size - printed, "%s%#x", printed ? "|" : "", flags);

	return printed;
}