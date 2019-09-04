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
struct TYPE_2__ {unsigned long x19; unsigned long x20; unsigned long pc; scalar_t__ sp; } ;
struct task_struct {int preempt_count; struct task_struct* next; TYPE_1__ cpu_context; int /*<<< orphan*/  priority; int /*<<< orphan*/  counter; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_RUNNING ; 
 scalar_t__ THREAD_SIZE ; 
 scalar_t__ get_free_page () ; 
 struct task_struct* kernel_task ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 scalar_t__ ret_from_fork ; 

int copy_process(unsigned long fn, unsigned long arg)
{
	preempt_disable();
	struct task_struct *p, *prev;

	p = (struct task_struct *) get_free_page();
	if (!p)
		return 1;
	p->priority = kernel_task->priority;
	p->state = TASK_RUNNING;
	p->counter = p->priority;
	p->preempt_count = 1; //disable preemtion until schedule_tail

	p->cpu_context.x19 = fn;
	p->cpu_context.x20 = arg;
	p->cpu_context.pc = (unsigned long)ret_from_fork;
	p->cpu_context.sp = (unsigned long)p + THREAD_SIZE;

	p->next = 0;
	prev = kernel_task;
	while(prev->next)
		prev = prev->next;
	prev->next = p;

	preempt_enable();
	return 0;
}