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
struct thread {int pid_; int tid; scalar_t__ mg; } ;
struct machine {int dummy; } ;
typedef  int pid_t ;

/* Variables and functions */
 struct thread* __machine__findnew_thread (struct machine*,int,int) ; 
 scalar_t__ map_groups__get (scalar_t__) ; 
 scalar_t__ map_groups__new (struct machine*) ; 
 int /*<<< orphan*/  thread__put (struct thread*) ; 

int thread__init_map_groups(struct thread *thread, struct machine *machine)
{
	pid_t pid = thread->pid_;

	if (pid == thread->tid || pid == -1) {
		thread->mg = map_groups__new(machine);
	} else {
		struct thread *leader = __machine__findnew_thread(machine, pid, pid);
		if (leader) {
			thread->mg = map_groups__get(leader->mg);
			thread__put(leader);
		}
	}

	return thread->mg ? 0 : -1;
}