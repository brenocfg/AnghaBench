#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct irqaction {void* dev_id; int flags; TYPE_1__* secondary; scalar_t__ thread; int /*<<< orphan*/  (* handler ) (unsigned int,void*) ;struct irqaction* next; } ;
struct TYPE_5__ {unsigned int irq; } ;
struct irq_desc {int /*<<< orphan*/  owner; TYPE_2__ irq_data; int /*<<< orphan*/  request_mutex; int /*<<< orphan*/  lock; struct irqaction* action; int /*<<< orphan*/ * affinity_hint; } ;
struct TYPE_4__ {scalar_t__ thread; } ;

/* Variables and functions */
 int IRQF_SHARED ; 
 int /*<<< orphan*/  WARN (int,char*,unsigned int) ; 
 scalar_t__ WARN_ON_ONCE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __synchronize_hardirq (struct irq_desc*,int) ; 
 int /*<<< orphan*/  chip_bus_lock (struct irq_desc*) ; 
 int /*<<< orphan*/  chip_bus_sync_unlock (struct irq_desc*) ; 
 int in_interrupt () ; 
 int /*<<< orphan*/  irq_chip_pm_put (TYPE_2__*) ; 
 int /*<<< orphan*/  irq_domain_deactivate_irq (TYPE_2__*) ; 
 int /*<<< orphan*/  irq_pm_remove_action (struct irq_desc*,struct irqaction*) ; 
 int /*<<< orphan*/  irq_release_resources (struct irq_desc*) ; 
 int /*<<< orphan*/  irq_remove_timings (struct irq_desc*) ; 
 int /*<<< orphan*/  irq_settings_clr_disable_unlazy (struct irq_desc*) ; 
 int /*<<< orphan*/  irq_shutdown (struct irq_desc*) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  kthread_stop (scalar_t__) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_task_struct (scalar_t__) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (unsigned int,void*) ; 
 int /*<<< orphan*/  unregister_handler_proc (unsigned int,struct irqaction*) ; 

__attribute__((used)) static struct irqaction *__free_irq(struct irq_desc *desc, void *dev_id)
{
	unsigned irq = desc->irq_data.irq;
	struct irqaction *action, **action_ptr;
	unsigned long flags;

	WARN(in_interrupt(), "Trying to free IRQ %d from IRQ context!\n", irq);

	mutex_lock(&desc->request_mutex);
	chip_bus_lock(desc);
	raw_spin_lock_irqsave(&desc->lock, flags);

	/*
	 * There can be multiple actions per IRQ descriptor, find the right
	 * one based on the dev_id:
	 */
	action_ptr = &desc->action;
	for (;;) {
		action = *action_ptr;

		if (!action) {
			WARN(1, "Trying to free already-free IRQ %d\n", irq);
			raw_spin_unlock_irqrestore(&desc->lock, flags);
			chip_bus_sync_unlock(desc);
			mutex_unlock(&desc->request_mutex);
			return NULL;
		}

		if (action->dev_id == dev_id)
			break;
		action_ptr = &action->next;
	}

	/* Found it - now remove it from the list of entries: */
	*action_ptr = action->next;

	irq_pm_remove_action(desc, action);

	/* If this was the last handler, shut down the IRQ line: */
	if (!desc->action) {
		irq_settings_clr_disable_unlazy(desc);
		/* Only shutdown. Deactivate after synchronize_hardirq() */
		irq_shutdown(desc);
	}

#ifdef CONFIG_SMP
	/* make sure affinity_hint is cleaned up */
	if (WARN_ON_ONCE(desc->affinity_hint))
		desc->affinity_hint = NULL;
#endif

	raw_spin_unlock_irqrestore(&desc->lock, flags);
	/*
	 * Drop bus_lock here so the changes which were done in the chip
	 * callbacks above are synced out to the irq chips which hang
	 * behind a slow bus (I2C, SPI) before calling synchronize_hardirq().
	 *
	 * Aside of that the bus_lock can also be taken from the threaded
	 * handler in irq_finalize_oneshot() which results in a deadlock
	 * because kthread_stop() would wait forever for the thread to
	 * complete, which is blocked on the bus lock.
	 *
	 * The still held desc->request_mutex() protects against a
	 * concurrent request_irq() of this irq so the release of resources
	 * and timing data is properly serialized.
	 */
	chip_bus_sync_unlock(desc);

	unregister_handler_proc(irq, action);

	/*
	 * Make sure it's not being used on another CPU and if the chip
	 * supports it also make sure that there is no (not yet serviced)
	 * interrupt in flight at the hardware level.
	 */
	__synchronize_hardirq(desc, true);

#ifdef CONFIG_DEBUG_SHIRQ
	/*
	 * It's a shared IRQ -- the driver ought to be prepared for an IRQ
	 * event to happen even now it's being freed, so let's make sure that
	 * is so by doing an extra call to the handler ....
	 *
	 * ( We do this after actually deregistering it, to make sure that a
	 *   'real' IRQ doesn't run in parallel with our fake. )
	 */
	if (action->flags & IRQF_SHARED) {
		local_irq_save(flags);
		action->handler(irq, dev_id);
		local_irq_restore(flags);
	}
#endif

	/*
	 * The action has already been removed above, but the thread writes
	 * its oneshot mask bit when it completes. Though request_mutex is
	 * held across this which prevents __setup_irq() from handing out
	 * the same bit to a newly requested action.
	 */
	if (action->thread) {
		kthread_stop(action->thread);
		put_task_struct(action->thread);
		if (action->secondary && action->secondary->thread) {
			kthread_stop(action->secondary->thread);
			put_task_struct(action->secondary->thread);
		}
	}

	/* Last action releases resources */
	if (!desc->action) {
		/*
		 * Reaquire bus lock as irq_release_resources() might
		 * require it to deallocate resources over the slow bus.
		 */
		chip_bus_lock(desc);
		/*
		 * There is no interrupt on the fly anymore. Deactivate it
		 * completely.
		 */
		raw_spin_lock_irqsave(&desc->lock, flags);
		irq_domain_deactivate_irq(&desc->irq_data);
		raw_spin_unlock_irqrestore(&desc->lock, flags);

		irq_release_resources(desc);
		chip_bus_sync_unlock(desc);
		irq_remove_timings(desc);
	}

	mutex_unlock(&desc->request_mutex);

	irq_chip_pm_put(&desc->irq_data);
	module_put(desc->owner);
	kfree(action->secondary);
	return action;
}