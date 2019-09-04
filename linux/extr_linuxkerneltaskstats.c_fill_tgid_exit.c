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
struct task_struct {TYPE_2__* sighand; TYPE_1__* signal; } ;
struct TYPE_4__ {int /*<<< orphan*/  siglock; } ;
struct TYPE_3__ {int /*<<< orphan*/  stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  delayacct_add_tsk (int /*<<< orphan*/ ,struct task_struct*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void fill_tgid_exit(struct task_struct *tsk)
{
	unsigned long flags;

	spin_lock_irqsave(&tsk->sighand->siglock, flags);
	if (!tsk->signal->stats)
		goto ret;

	/*
	 * Each accounting subsystem calls its functions here to
	 * accumalate its per-task stats for tsk, into the per-tgid structure
	 *
	 *	per-task-foo(tsk->signal->stats, tsk);
	 */
	delayacct_add_tsk(tsk->signal->stats, tsk);
ret:
	spin_unlock_irqrestore(&tsk->sighand->siglock, flags);
	return;
}