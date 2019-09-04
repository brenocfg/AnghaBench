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
struct thread_trace {size_t (* ret_scnprintf ) (char*,size_t,struct syscall_arg*) ;} ;
struct syscall_arg {int /*<<< orphan*/  thread; } ;

/* Variables and functions */
 struct thread_trace* thread__priv (int /*<<< orphan*/ ) ; 

void syscall_arg__set_ret_scnprintf(struct syscall_arg *arg,
				    size_t (*ret_scnprintf)(char *bf, size_t size, struct syscall_arg *arg))
{
	struct thread_trace *ttrace = thread__priv(arg->thread);

	ttrace->ret_scnprintf = ret_scnprintf;
}