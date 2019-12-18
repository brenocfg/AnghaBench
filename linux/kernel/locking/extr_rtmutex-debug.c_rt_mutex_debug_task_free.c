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
struct TYPE_2__ {int /*<<< orphan*/  rb_root; } ;
struct task_struct {int pi_blocked_on; TYPE_1__ pi_waiters; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_LOCKS_WARN_ON (int) ; 
 int /*<<< orphan*/  RB_EMPTY_ROOT (int /*<<< orphan*/ *) ; 

void rt_mutex_debug_task_free(struct task_struct *task)
{
	DEBUG_LOCKS_WARN_ON(!RB_EMPTY_ROOT(&task->pi_waiters.rb_root));
	DEBUG_LOCKS_WARN_ON(task->pi_blocked_on);
}