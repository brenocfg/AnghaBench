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
struct task_struct {TYPE_1__* sighand; int /*<<< orphan*/  blocked; } ;
typedef  int /*<<< orphan*/  sigset_t ;
struct TYPE_2__ {int /*<<< orphan*/  siglock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __set_task_blocked (struct task_struct*,int /*<<< orphan*/  const*) ; 
 struct task_struct* current ; 
 scalar_t__ sigequalsets (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void __set_current_blocked(const sigset_t *newset)
{
	struct task_struct *tsk = current;

	/*
	 * In case the signal mask hasn't changed, there is nothing we need
	 * to do. The current->blocked shouldn't be modified by other task.
	 */
	if (sigequalsets(&tsk->blocked, newset))
		return;

	spin_lock_irq(&tsk->sighand->siglock);
	__set_task_blocked(tsk, newset);
	spin_unlock_irq(&tsk->sighand->siglock);
}