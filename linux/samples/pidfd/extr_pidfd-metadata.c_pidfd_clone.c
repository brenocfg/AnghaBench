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
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int SIGCHLD ; 
 int /*<<< orphan*/  __clone2 (int /*<<< orphan*/ ,char**,size_t,int,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  clone (int /*<<< orphan*/ ,char**,int,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  do_child ; 

__attribute__((used)) static pid_t pidfd_clone(int flags, int *pidfd)
{
	size_t stack_size = 1024;
	char *stack[1024] = { 0 };

#ifdef __ia64__
	return __clone2(do_child, stack, stack_size, flags | SIGCHLD, NULL, pidfd);
#else
	return clone(do_child, stack + stack_size, flags | SIGCHLD, NULL, pidfd);
#endif
}