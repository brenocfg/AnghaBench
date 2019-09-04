#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int max; int /*<<< orphan*/ * table; } ;
struct thread_trace {TYPE_1__ paths; } ;
struct syscall_arg {int val; int /*<<< orphan*/  thread; } ;

/* Variables and functions */
 size_t syscall_arg__scnprintf_fd (char*,size_t,struct syscall_arg*) ; 
 struct thread_trace* thread__priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static size_t syscall_arg__scnprintf_close_fd(char *bf, size_t size,
					      struct syscall_arg *arg)
{
	int fd = arg->val;
	size_t printed = syscall_arg__scnprintf_fd(bf, size, arg);
	struct thread_trace *ttrace = thread__priv(arg->thread);

	if (ttrace && fd >= 0 && fd <= ttrace->paths.max)
		zfree(&ttrace->paths.table[fd]);

	return printed;
}