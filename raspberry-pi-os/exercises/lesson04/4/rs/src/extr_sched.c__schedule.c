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
struct task_struct {scalar_t__ state; int counter; int priority; struct task_struct* next; } ;

/* Variables and functions */
 scalar_t__ TASK_RUNNING ; 
 struct task_struct* init ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  switch_to (struct task_struct*) ; 

void _schedule(void) {
  preempt_disable();
  int c;
  struct task_struct *p, *next;
  while (1) {
    c = -1;
    for (p = init; p; p = p->next) {
      if (p && p->state == TASK_RUNNING && p->counter > c) {
        c = p->counter;
        next = p;
      }
    }
    if (c) {
      break;
    }
    for (p = init; p; p = p->next) {
      if (p) {
        p->counter = (p->counter >> 1) + p->priority;
      }
    }
  }
  switch_to(next);
  preempt_enable();
}