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
struct __test_metadata {int dummy; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int ESRCH ; 
 int /*<<< orphan*/  EXPECT_EQ (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  PTRACE_EVENTMSG_SYSCALL_ENTRY ; 
 int /*<<< orphan*/  PTRACE_EVENTMSG_SYSCALL_EXIT ; 
 int /*<<< orphan*/  PTRACE_GETEVENTMSG ; 
 int __NR_getpid ; 
 int __NR_getppid ; 
 int __NR_gettid ; 
 int __NR_openat ; 
 int /*<<< orphan*/  change_syscall (struct __test_metadata*,int /*<<< orphan*/ ,int,int) ; 
 int get_syscall (struct __test_metadata*,int /*<<< orphan*/ ) ; 
 int ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long*) ; 

void tracer_ptrace(struct __test_metadata *_metadata, pid_t tracee,
		   int status, void *args)
{
	int ret, nr;
	unsigned long msg;
	static bool entry;

	/*
	 * The traditional way to tell PTRACE_SYSCALL entry/exit
	 * is by counting.
	 */
	entry = !entry;

	/* Make sure we got an appropriate message. */
	ret = ptrace(PTRACE_GETEVENTMSG, tracee, NULL, &msg);
	EXPECT_EQ(0, ret);
	EXPECT_EQ(entry ? PTRACE_EVENTMSG_SYSCALL_ENTRY
			: PTRACE_EVENTMSG_SYSCALL_EXIT, msg);

	if (!entry)
		return;

	nr = get_syscall(_metadata, tracee);

	if (nr == __NR_getpid)
		change_syscall(_metadata, tracee, __NR_getppid, 0);
	if (nr == __NR_gettid)
		change_syscall(_metadata, tracee, -1, 45000);
	if (nr == __NR_openat)
		change_syscall(_metadata, tracee, -1, -ESRCH);
}