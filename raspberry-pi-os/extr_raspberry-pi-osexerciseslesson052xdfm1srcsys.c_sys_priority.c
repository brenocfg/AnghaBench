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
struct task_struct {unsigned long priority; } ;

/* Variables and functions */
 int NR_TASKS ; 
 int /*<<< orphan*/  schedule () ; 
 struct task_struct** task ; 

void sys_priority(int pid, unsigned long priority)
{
    if(pid >= NR_TASKS)
    {
	return;
    }
    struct task_struct *p = task[pid];
    p->priority = priority;
    schedule();
}