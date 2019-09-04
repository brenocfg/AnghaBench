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
struct task_struct {int flags; int /*<<< orphan*/  pid; int /*<<< orphan*/  comm; } ;
struct irqaction {int /*<<< orphan*/  thread_flags; int /*<<< orphan*/  irq; } ;
struct irq_desc {int dummy; } ;
struct callback_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQTF_RUNTHREAD ; 
 int PF_EXITING ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  irq_finalize_oneshot (struct irq_desc*,struct irqaction*) ; 
 struct irq_desc* irq_to_desc (int /*<<< orphan*/ ) ; 
 struct irqaction* kthread_data (struct task_struct*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_threads_waitq (struct irq_desc*) ; 

__attribute__((used)) static void irq_thread_dtor(struct callback_head *unused)
{
	struct task_struct *tsk = current;
	struct irq_desc *desc;
	struct irqaction *action;

	if (WARN_ON_ONCE(!(current->flags & PF_EXITING)))
		return;

	action = kthread_data(tsk);

	pr_err("exiting task \"%s\" (%d) is an active IRQ thread (irq %d)\n",
	       tsk->comm, tsk->pid, action->irq);


	desc = irq_to_desc(action->irq);
	/*
	 * If IRQTF_RUNTHREAD is set, we need to decrement
	 * desc->threads_active and wake possible waiters.
	 */
	if (test_and_clear_bit(IRQTF_RUNTHREAD, &action->thread_flags))
		wake_threads_waitq(desc);

	/* Prevent a stale desc->threads_oneshot */
	irq_finalize_oneshot(desc, action);
}