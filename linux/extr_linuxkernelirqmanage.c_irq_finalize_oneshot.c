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
struct irqaction {scalar_t__ handler; int /*<<< orphan*/  thread_mask; int /*<<< orphan*/  thread_flags; } ;
struct irq_desc {int istate; int /*<<< orphan*/  lock; int /*<<< orphan*/  irq_data; int /*<<< orphan*/  threads_oneshot; } ;

/* Variables and functions */
 int IRQS_ONESHOT ; 
 int /*<<< orphan*/  IRQTF_RUNTHREAD ; 
 int /*<<< orphan*/  chip_bus_lock (struct irq_desc*) ; 
 int /*<<< orphan*/  chip_bus_sync_unlock (struct irq_desc*) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 scalar_t__ irq_forced_secondary_handler ; 
 int /*<<< orphan*/  irqd_irq_disabled (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irqd_irq_inprogress (int /*<<< orphan*/ *) ; 
 scalar_t__ irqd_irq_masked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unmask_threaded_irq (struct irq_desc*) ; 

__attribute__((used)) static void irq_finalize_oneshot(struct irq_desc *desc,
				 struct irqaction *action)
{
	if (!(desc->istate & IRQS_ONESHOT) ||
	    action->handler == irq_forced_secondary_handler)
		return;
again:
	chip_bus_lock(desc);
	raw_spin_lock_irq(&desc->lock);

	/*
	 * Implausible though it may be we need to protect us against
	 * the following scenario:
	 *
	 * The thread is faster done than the hard interrupt handler
	 * on the other CPU. If we unmask the irq line then the
	 * interrupt can come in again and masks the line, leaves due
	 * to IRQS_INPROGRESS and the irq line is masked forever.
	 *
	 * This also serializes the state of shared oneshot handlers
	 * versus "desc->threads_onehsot |= action->thread_mask;" in
	 * irq_wake_thread(). See the comment there which explains the
	 * serialization.
	 */
	if (unlikely(irqd_irq_inprogress(&desc->irq_data))) {
		raw_spin_unlock_irq(&desc->lock);
		chip_bus_sync_unlock(desc);
		cpu_relax();
		goto again;
	}

	/*
	 * Now check again, whether the thread should run. Otherwise
	 * we would clear the threads_oneshot bit of this thread which
	 * was just set.
	 */
	if (test_bit(IRQTF_RUNTHREAD, &action->thread_flags))
		goto out_unlock;

	desc->threads_oneshot &= ~action->thread_mask;

	if (!desc->threads_oneshot && !irqd_irq_disabled(&desc->irq_data) &&
	    irqd_irq_masked(&desc->irq_data))
		unmask_threaded_irq(desc);

out_unlock:
	raw_spin_unlock_irq(&desc->lock);
	chip_bus_sync_unlock(desc);
}