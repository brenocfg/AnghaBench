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
struct kernel_clone_args {unsigned long flags; unsigned long exit_signal; unsigned long stack; unsigned long stack_size; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 unsigned long CLONE_UNTRACED ; 
 unsigned long CLONE_VM ; 
 unsigned long CSIGNAL ; 
 int /*<<< orphan*/  _do_fork (struct kernel_clone_args*) ; 

pid_t kernel_thread(int (*fn)(void *), void *arg, unsigned long flags)
{
	struct kernel_clone_args args = {
		.flags		= ((flags | CLONE_VM | CLONE_UNTRACED) & ~CSIGNAL),
		.exit_signal	= (flags & CSIGNAL),
		.stack		= (unsigned long)fn,
		.stack_size	= (unsigned long)arg,
	};

	return _do_fork(&args);
}