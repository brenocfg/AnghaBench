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
struct task_struct {char state; int exit_state; int /*<<< orphan*/  mm; } ;
struct TYPE_2__ {int irq_depth; } ;

/* Variables and functions */
 int EXIT_DEAD ; 
 int EXIT_ZOMBIE ; 
 char TASK_INTERRUPTIBLE ; 
 char TASK_STOPPED ; 
 char TASK_TRACED ; 
 char TASK_UNINTERRUPTIBLE ; 
 scalar_t__ is_idle_task (struct task_struct const*) ; 
 int kdb_initial_cpu ; 
 int kdb_process_cpu (struct task_struct const*) ; 
 int /*<<< orphan*/  kdb_task_has_cpu (struct task_struct const*) ; 
 TYPE_1__* kgdb_info ; 
 scalar_t__ probe_kernel_read (unsigned long*,char*,int) ; 

char kdb_task_state_char (const struct task_struct *p)
{
	int cpu;
	char state;
	unsigned long tmp;

	if (!p || probe_kernel_read(&tmp, (char *)p, sizeof(unsigned long)))
		return 'E';

	cpu = kdb_process_cpu(p);
	state = (p->state == 0) ? 'R' :
		(p->state < 0) ? 'U' :
		(p->state & TASK_UNINTERRUPTIBLE) ? 'D' :
		(p->state & TASK_STOPPED) ? 'T' :
		(p->state & TASK_TRACED) ? 'C' :
		(p->exit_state & EXIT_ZOMBIE) ? 'Z' :
		(p->exit_state & EXIT_DEAD) ? 'E' :
		(p->state & TASK_INTERRUPTIBLE) ? 'S' : '?';
	if (is_idle_task(p)) {
		/* Idle task.  Is it really idle, apart from the kdb
		 * interrupt? */
		if (!kdb_task_has_cpu(p) || kgdb_info[cpu].irq_depth == 1) {
			if (cpu != kdb_initial_cpu)
				state = 'I';	/* idle task */
		}
	} else if (!p->mm && state == 'S') {
		state = 'M';	/* sleeping system daemon */
	}
	return state;
}