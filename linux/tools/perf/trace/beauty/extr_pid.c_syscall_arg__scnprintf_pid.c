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
struct trace {int /*<<< orphan*/  host; } ;
struct thread {scalar_t__ comm_set; } ;
struct syscall_arg {int val; struct trace* trace; } ;

/* Variables and functions */
 struct thread* machine__findnew_thread (int /*<<< orphan*/ ,int,int) ; 
 size_t scnprintf (char*,size_t,char*,int) ; 
 int thread__comm_str (struct thread*) ; 
 int /*<<< orphan*/  thread__put (struct thread*) ; 
 int /*<<< orphan*/  thread__set_comm_from_proc (struct thread*) ; 

size_t syscall_arg__scnprintf_pid(char *bf, size_t size, struct syscall_arg *arg)
{
	int pid = arg->val;
	struct trace *trace = arg->trace;
	size_t printed = scnprintf(bf, size, "%d", pid);
	struct thread *thread = machine__findnew_thread(trace->host, pid, pid);

	if (thread != NULL) {
		if (!thread->comm_set)
			thread__set_comm_from_proc(thread);

		if (thread->comm_set)
			printed += scnprintf(bf + printed, size - printed,
					     " (%s)", thread__comm_str(thread));
		thread__put(thread);
	}

	return printed;
}