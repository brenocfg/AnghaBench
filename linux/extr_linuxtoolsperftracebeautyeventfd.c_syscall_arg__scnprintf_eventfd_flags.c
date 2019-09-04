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
 int EFD_CLOEXEC ; 
 int EFD_NONBLOCK ; 
 int EFD_SEMAPHORE ; 
 size_t scnprintf (char*,size_t,char*,...) ; 

__attribute__((used)) static size_t syscall_arg__scnprintf_eventfd_flags(char *bf, size_t size, struct syscall_arg *arg)
{
	int printed = 0, flags = arg->val;

	if (flags == 0)
		return scnprintf(bf, size, "NONE");
#define	P_FLAG(n) \
	if (flags & EFD_##n) { \
		printed += scnprintf(bf + printed, size - printed, "%s%s", printed ? "|" : "", #n); \
		flags &= ~EFD_##n; \
	}

	P_FLAG(SEMAPHORE);
	P_FLAG(CLOEXEC);
	P_FLAG(NONBLOCK);
#undef P_FLAG

	if (flags)
		printed += scnprintf(bf + printed, size - printed, "%s%#x", printed ? "|" : "", flags);

	return printed;
}