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
 int SECCOMP_FILTER_FLAG_TSYNC ; 
 scalar_t__ scnprintf (char*,size_t,char*,char*,...) ; 

__attribute__((used)) static size_t syscall_arg__scnprintf_seccomp_flags(char *bf, size_t size,
						   struct syscall_arg *arg)
{
	int printed = 0, flags = arg->val;

#define	P_FLAG(n) \
	if (flags & SECCOMP_FILTER_FLAG_##n) { \
		printed += scnprintf(bf + printed, size - printed, "%s%s", printed ? "|" : "", #n); \
		flags &= ~SECCOMP_FILTER_FLAG_##n; \
	}

	P_FLAG(TSYNC);
#undef P_FLAG

	if (flags)
		printed += scnprintf(bf + printed, size - printed, "%s%#x", printed ? "|" : "", flags);

	return printed;
}