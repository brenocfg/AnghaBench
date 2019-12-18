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
struct task_struct {scalar_t__ state; int counter; int priority; struct task_struct* next_task; } ;

/* Variables and functions */
 scalar_t__ TASK_RUNNING ; 
 struct task_struct* initial_task ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  switch_to (struct task_struct*) ; 

void _schedule(void)
{
	preempt_disable();
	int c;
	struct task_struct * p, * next_task;
	while (1) {
		c = -1;
		//next = 0;
		// Point to the first task (initial_task) and loop until p != 0
		for (p = initial_task; p; p = p->next_task){
			//p = task[i];   we don't need more
			if (p && p->state == TASK_RUNNING && p->counter > c) {
				c = p->counter;
				next_task = p;			// point to next task
			}
		}
		if (c) {
			break;
		}
		// Same here
		for (p = initial_task; p; p = p->next_task) {
			//p = task[i]; we don't need more
			if (p) {
				p->counter = (p->counter >> 1) + p->priority;
			}
		}
	}
	switch_to(next_task);		// next_task is a pointer to a task
	preempt_enable();
}