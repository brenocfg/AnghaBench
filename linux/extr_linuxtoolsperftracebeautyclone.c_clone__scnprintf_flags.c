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
 unsigned long CLONE_CHILD_CLEARTID ; 
 unsigned long CLONE_CHILD_SETTID ; 
 unsigned long CLONE_DETACHED ; 
 unsigned long CLONE_FILES ; 
 unsigned long CLONE_FS ; 
 unsigned long CLONE_IO ; 
 unsigned long CLONE_NEWCGROUP ; 
 unsigned long CLONE_NEWIPC ; 
 unsigned long CLONE_NEWNET ; 
 unsigned long CLONE_NEWNS ; 
 unsigned long CLONE_NEWPID ; 
 unsigned long CLONE_NEWUSER ; 
 unsigned long CLONE_NEWUTS ; 
 unsigned long CLONE_PARENT ; 
 unsigned long CLONE_PARENT_SETTID ; 
 unsigned long CLONE_PTRACE ; 
 unsigned long CLONE_SETTLS ; 
 unsigned long CLONE_SIGHAND ; 
 unsigned long CLONE_SYSVSEM ; 
 unsigned long CLONE_THREAD ; 
 unsigned long CLONE_UNTRACED ; 
 unsigned long CLONE_VFORK ; 
 unsigned long CLONE_VM ; 
 scalar_t__ scnprintf (char*,size_t,char*,char*,...) ; 

__attribute__((used)) static size_t clone__scnprintf_flags(unsigned long flags, char *bf, size_t size)
{
	int printed = 0;

#define	P_FLAG(n) \
	if (flags & CLONE_##n) { \
		printed += scnprintf(bf + printed, size - printed, "%s%s", printed ? "|" : "", #n); \
		flags &= ~CLONE_##n; \
	}

	P_FLAG(VM);
	P_FLAG(FS);
	P_FLAG(FILES);
	P_FLAG(SIGHAND);
	P_FLAG(PTRACE);
	P_FLAG(VFORK);
	P_FLAG(PARENT);
	P_FLAG(THREAD);
	P_FLAG(NEWNS);
	P_FLAG(SYSVSEM);
	P_FLAG(SETTLS);
	P_FLAG(PARENT_SETTID);
	P_FLAG(CHILD_CLEARTID);
	P_FLAG(DETACHED);
	P_FLAG(UNTRACED);
	P_FLAG(CHILD_SETTID);
	P_FLAG(NEWCGROUP);
	P_FLAG(NEWUTS);
	P_FLAG(NEWIPC);
	P_FLAG(NEWUSER);
	P_FLAG(NEWPID);
	P_FLAG(NEWNET);
	P_FLAG(IO);
#undef P_FLAG

	if (flags)
		printed += scnprintf(bf + printed, size - printed, "%s%#x", printed ? "|" : "", flags);

	return printed;
}