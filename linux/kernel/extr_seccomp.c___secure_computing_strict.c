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
 int /*<<< orphan*/  SECCOMP_RET_KILL_THREAD ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  do_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_stack () ; 
 int* get_compat_mode1_syscalls () ; 
 scalar_t__ in_compat_syscall () ; 
 int* mode1_syscalls ; 
 int /*<<< orphan*/  seccomp_log (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void __secure_computing_strict(int this_syscall)
{
	const int *syscall_whitelist = mode1_syscalls;
#ifdef CONFIG_COMPAT
	if (in_compat_syscall())
		syscall_whitelist = get_compat_mode1_syscalls();
#endif
	do {
		if (*syscall_whitelist == this_syscall)
			return;
	} while (*++syscall_whitelist);

#ifdef SECCOMP_DEBUG
	dump_stack();
#endif
	seccomp_log(this_syscall, SIGKILL, SECCOMP_RET_KILL_THREAD, true);
	do_exit(SIGKILL);
}