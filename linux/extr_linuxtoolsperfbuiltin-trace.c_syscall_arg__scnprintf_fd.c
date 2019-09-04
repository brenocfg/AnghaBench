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
struct syscall_arg {int val; int /*<<< orphan*/  trace; int /*<<< orphan*/  thread; } ;

/* Variables and functions */
 size_t scnprintf (char*,size_t,char*,...) ; 
 char* thread__fd_path (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

size_t syscall_arg__scnprintf_fd(char *bf, size_t size, struct syscall_arg *arg)
{
	int fd = arg->val;
	size_t printed = scnprintf(bf, size, "%d", fd);
	const char *path = thread__fd_path(arg->thread, fd, arg->trace);

	if (path)
		printed += scnprintf(bf + printed, size - printed, "<%s>", path);

	return printed;
}