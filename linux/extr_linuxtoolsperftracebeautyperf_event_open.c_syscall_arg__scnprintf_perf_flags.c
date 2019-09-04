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
 int PERF_FLAG_FD_CLOEXEC ; 
 int PERF_FLAG_FD_NO_GROUP ; 
 int PERF_FLAG_FD_OUTPUT ; 
 int PERF_FLAG_PID_CGROUP ; 
 scalar_t__ scnprintf (char*,size_t,char*,char*,...) ; 

__attribute__((used)) static size_t syscall_arg__scnprintf_perf_flags(char *bf, size_t size,
						struct syscall_arg *arg)
{
	int printed = 0, flags = arg->val;

	if (flags == 0)
		return 0;

#define	P_FLAG(n) \
	if (flags & PERF_FLAG_##n) { \
		printed += scnprintf(bf + printed, size - printed, "%s%s", printed ? "|" : "", #n); \
		flags &= ~PERF_FLAG_##n; \
	}

	P_FLAG(FD_NO_GROUP);
	P_FLAG(FD_OUTPUT);
	P_FLAG(PID_CGROUP);
	P_FLAG(FD_CLOEXEC);
#undef P_FLAG

	if (flags)
		printed += scnprintf(bf + printed, size - printed, "%s%#x", printed ? "|" : "", flags);

	return printed;
}