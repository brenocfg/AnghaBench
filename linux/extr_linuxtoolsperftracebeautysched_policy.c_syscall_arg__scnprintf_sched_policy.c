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
 int SCHED_DEADLINE ; 
 int SCHED_POLICY_MASK ; 
 int SCHED_RESET_ON_FORK ; 
 size_t scnprintf (char*,size_t,char*,...) ; 

__attribute__((used)) static size_t syscall_arg__scnprintf_sched_policy(char *bf, size_t size,
						  struct syscall_arg *arg)
{
	const char *policies[] = {
		"NORMAL", "FIFO", "RR", "BATCH", "ISO", "IDLE", "DEADLINE",
	};
	size_t printed;
	int policy = arg->val,
	    flags = policy & ~SCHED_POLICY_MASK;

	policy &= SCHED_POLICY_MASK;
	if (policy <= SCHED_DEADLINE)
		printed = scnprintf(bf, size, "%s", policies[policy]);
	else
		printed = scnprintf(bf, size, "%#x", policy);

#define	P_POLICY_FLAG(n) \
	if (flags & SCHED_##n) { \
		printed += scnprintf(bf + printed, size - printed, "|%s", #n); \
		flags &= ~SCHED_##n; \
	}

	P_POLICY_FLAG(RESET_ON_FORK);
#undef P_POLICY_FLAG

	if (flags)
		printed += scnprintf(bf + printed, size - printed, "|%#x", flags);

	return printed;
}