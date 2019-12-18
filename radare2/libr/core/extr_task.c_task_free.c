#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  cons_context; int /*<<< orphan*/  dispatch_lock; int /*<<< orphan*/  dispatch_cond; int /*<<< orphan*/  running_sem; int /*<<< orphan*/  thread; struct TYPE_4__* res; struct TYPE_4__* cmd; } ;
typedef  TYPE_1__ RCoreTask ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  r_cons_context_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_th_cond_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_th_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_th_lock_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_th_sem_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void task_free (RCoreTask *task) {
	if (!task) {
		return;
	}
	free (task->cmd);
	free (task->res);
	r_th_free (task->thread);
	r_th_sem_free (task->running_sem);
	r_th_cond_free (task->dispatch_cond);
	r_th_lock_free (task->dispatch_lock);
	r_cons_context_free (task->cons_context);
	free (task);
}