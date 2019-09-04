#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int NR_TASKS ; 
 int /*<<< orphan*/  TASK_ZOMBIE ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  schedule () ; 
 TYPE_1__** task ; 

void exit_process(){
	preempt_disable();
	for (int i = 0; i < NR_TASKS; i++){
		if (task[i] == current) {
			task[i]->state = TASK_ZOMBIE;
			break;
		}
	}
	preempt_enable();
	schedule();
}