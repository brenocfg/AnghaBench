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
struct threads {struct thread* last_match; } ;
struct thread {int tid; } ;
struct machine {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  machine__update_thread_pid (struct machine*,struct thread*,int) ; 
 struct thread* thread__get (struct thread*) ; 

__attribute__((used)) static struct thread*
__threads__get_last_match(struct threads *threads, struct machine *machine,
			  int pid, int tid)
{
	struct thread *th;

	th = threads->last_match;
	if (th != NULL) {
		if (th->tid == tid) {
			machine__update_thread_pid(machine, th, pid);
			return thread__get(th);
		}

		threads->last_match = NULL;
	}

	return NULL;
}