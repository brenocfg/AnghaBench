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
struct thread {int pid_; int tid; } ;
struct machine {int dummy; } ;

/* Variables and functions */
 struct thread* machine__find_thread (struct machine*,int,int) ; 
 struct thread* thread__get (struct thread*) ; 

struct thread *thread__main_thread(struct machine *machine, struct thread *thread)
{
	if (thread->pid_ == thread->tid)
		return thread__get(thread);

	if (thread->pid_ == -1)
		return NULL;

	return machine__find_thread(machine, thread->pid_, thread->pid_);
}