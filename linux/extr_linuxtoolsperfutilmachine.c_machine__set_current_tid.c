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
struct thread {int cpu; } ;
struct machine {int* current_tid; } ;
typedef  int pid_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int MAX_NR_CPUS ; 
 int* calloc (int,int) ; 
 struct thread* machine__findnew_thread (struct machine*,int,int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  thread__put (struct thread*) ; 

int machine__set_current_tid(struct machine *machine, int cpu, pid_t pid,
			     pid_t tid)
{
	struct thread *thread;

	if (cpu < 0)
		return -EINVAL;

	if (!machine->current_tid) {
		int i;

		machine->current_tid = calloc(MAX_NR_CPUS, sizeof(pid_t));
		if (!machine->current_tid)
			return -ENOMEM;
		for (i = 0; i < MAX_NR_CPUS; i++)
			machine->current_tid[i] = -1;
	}

	if (cpu >= MAX_NR_CPUS) {
		pr_err("Requested CPU %d too large. ", cpu);
		pr_err("Consider raising MAX_NR_CPUS\n");
		return -EINVAL;
	}

	machine->current_tid[cpu] = tid;

	thread = machine__findnew_thread(machine, pid, tid);
	if (!thread)
		return -ENOMEM;

	thread->cpu = cpu;
	thread__put(thread);

	return 0;
}