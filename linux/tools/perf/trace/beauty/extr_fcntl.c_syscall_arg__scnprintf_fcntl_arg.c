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
struct syscall_arg {int show_string_prefix; int /*<<< orphan*/  val; } ;

/* Variables and functions */
 int F_DUPFD ; 
 int F_GETLK ; 
 int F_GETOWN_EX ; 
 int F_GET_FILE_RW_HINT ; 
 int F_GET_RW_HINT ; 
 int F_OFD_GETLK ; 
 int F_OFD_SETLK ; 
 int F_OFD_SETLKW ; 
 int F_SETFD ; 
 int F_SETFL ; 
 int F_SETLEASE ; 
 int F_SETLK ; 
 int F_SETLKW ; 
 int F_SETOWN ; 
 int F_SETOWN_EX ; 
 int F_SET_FILE_RW_HINT ; 
 int F_SET_RW_HINT ; 
 size_t fcntl__scnprintf_getfd (int /*<<< orphan*/ ,char*,size_t,int) ; 
 size_t fcntl__scnprintf_getlease (int /*<<< orphan*/ ,char*,size_t,int) ; 
 size_t open__scnprintf_flags (int /*<<< orphan*/ ,char*,size_t,int) ; 
 size_t syscall_arg__scnprintf_fd (char*,size_t,struct syscall_arg*) ; 
 size_t syscall_arg__scnprintf_hex (char*,size_t,struct syscall_arg*) ; 
 size_t syscall_arg__scnprintf_long (char*,size_t,struct syscall_arg*) ; 
 size_t syscall_arg__scnprintf_pid (char*,size_t,struct syscall_arg*) ; 
 int syscall_arg__val (struct syscall_arg*,int) ; 

size_t syscall_arg__scnprintf_fcntl_arg(char *bf, size_t size, struct syscall_arg *arg)
{
	bool show_prefix = arg->show_string_prefix;
	int cmd = syscall_arg__val(arg, 1);

	if (cmd == F_DUPFD)
		return syscall_arg__scnprintf_fd(bf, size, arg);

	if (cmd == F_SETFD)
		return fcntl__scnprintf_getfd(arg->val, bf, size, show_prefix);

	if (cmd == F_SETFL)
		return open__scnprintf_flags(arg->val, bf, size, show_prefix);

	if (cmd == F_SETOWN)
		return syscall_arg__scnprintf_pid(bf, size, arg);

	if (cmd == F_SETLEASE)
		return fcntl__scnprintf_getlease(arg->val, bf, size, show_prefix);
	/*
	 * We still don't grab the contents of pointers on entry or exit,
	 * so just print them as hex numbers
	 */
	if (cmd == F_SETLK || cmd == F_SETLKW || cmd == F_GETLK ||
	    cmd == F_OFD_SETLK || cmd == F_OFD_SETLKW || cmd == F_OFD_GETLK ||
	    cmd == F_GETOWN_EX || cmd == F_SETOWN_EX ||
	    cmd == F_GET_RW_HINT || cmd == F_SET_RW_HINT ||
	    cmd == F_GET_FILE_RW_HINT || cmd == F_SET_FILE_RW_HINT)
		return syscall_arg__scnprintf_hex(bf, size, arg);

	return syscall_arg__scnprintf_long(bf, size, arg);
}