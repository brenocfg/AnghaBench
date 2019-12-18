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
struct task_struct {long priority; long counter; int preempt_count; TYPE_1__ cpu_context; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_RUNNING ; 
 scalar_t__ THREAD_SIZE ; 
 scalar_t__ get_free_page () ; 
 int /*<<< orphan*/  nr_tasks ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 scalar_t__ ret_from_fork ; 
 struct task_struct** task ; 

int copy_process(unsigned long fn, unsigned long arg, long pri) {
  preempt_disable();
  struct task_struct *p;

  p = (struct task_struct *)get_free_page();
  if (!p)
    return 1;
  p->priority = pri;
  p->state = TASK_RUNNING;
  p->counter = p->priority;
  p->preempt_count = 1; // disable preemtion untill schedule_tail

  p->cpu_context.x19 = fn;
  p->cpu_context.x20 = arg;
  p->cpu_context.pc = (unsigned long)ret_from_fork;
  p->cpu_context.sp = (unsigned long)p + THREAD_SIZE;
  int pid = nr_tasks++;
  task[pid] = p;
  preempt_enable();
  return 0;
}