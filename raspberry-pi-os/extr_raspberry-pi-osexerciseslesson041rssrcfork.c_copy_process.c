#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned long x19; unsigned long x20; unsigned long pc; int sp; } ;
struct task_struct {int preempt_count; TYPE_1__ cpu_context; int /*<<< orphan*/  priority; int /*<<< orphan*/  counter; int /*<<< orphan*/  state; } ;
struct TYPE_4__ {int /*<<< orphan*/  priority; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_RUNNING ; 
 int THREAD_SIZE ; 
 TYPE_2__* current ; 
 scalar_t__ get_free_page () ; 
 int /*<<< orphan*/  nr_tasks ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 scalar_t__ ret_from_fork ; 
 struct task_struct** task ; 

int copy_process(unsigned long fn, unsigned long arg) {
  preempt_disable();
  struct task_struct *p;

  p = (struct task_struct *)get_free_page();
  if (!p)
    return 1;
  p->priority = current->priority;
  p->state = TASK_RUNNING;
  p->counter = p->priority;
  p->preempt_count = 1; // disable preemtion untill schedule_tail

  p->cpu_context.x19 = fn;
  p->cpu_context.x20 = arg;
  p->cpu_context.pc = (unsigned long)ret_from_fork;
  p->cpu_context.sp = (unsigned long)p + THREAD_SIZE;
  int pid = nr_tasks++;
  task[pid] = p;
  printf("copy_process: pid=%d, sp=%x\r\n", pid, p->cpu_context.sp);
  preempt_enable();
  return 0;
}