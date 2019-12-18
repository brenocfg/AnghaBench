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
struct irqaction {int flags; scalar_t__ handler; scalar_t__ thread_fn; int /*<<< orphan*/  thread_flags; int /*<<< orphan*/  name; TYPE_1__* secondary; int /*<<< orphan*/  irq; int /*<<< orphan*/  dev_id; } ;
struct TYPE_2__ {scalar_t__ thread_fn; int /*<<< orphan*/  name; int /*<<< orphan*/  irq; int /*<<< orphan*/  dev_id; int /*<<< orphan*/  handler; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IRQF_NO_THREAD ; 
 int IRQF_ONESHOT ; 
 int IRQF_PERCPU ; 
 int /*<<< orphan*/  IRQTF_FORCED_THREAD ; 
 int /*<<< orphan*/  force_irqthreads ; 
 scalar_t__ irq_default_primary_handler ; 
 int /*<<< orphan*/  irq_forced_secondary_handler ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int irq_setup_forced_threading(struct irqaction *new)
{
	if (!force_irqthreads)
		return 0;
	if (new->flags & (IRQF_NO_THREAD | IRQF_PERCPU | IRQF_ONESHOT))
		return 0;

	/*
	 * No further action required for interrupts which are requested as
	 * threaded interrupts already
	 */
	if (new->handler == irq_default_primary_handler)
		return 0;

	new->flags |= IRQF_ONESHOT;

	/*
	 * Handle the case where we have a real primary handler and a
	 * thread handler. We force thread them as well by creating a
	 * secondary action.
	 */
	if (new->handler && new->thread_fn) {
		/* Allocate the secondary action */
		new->secondary = kzalloc(sizeof(struct irqaction), GFP_KERNEL);
		if (!new->secondary)
			return -ENOMEM;
		new->secondary->handler = irq_forced_secondary_handler;
		new->secondary->thread_fn = new->thread_fn;
		new->secondary->dev_id = new->dev_id;
		new->secondary->irq = new->irq;
		new->secondary->name = new->name;
	}
	/* Deal with the primary handler */
	set_bit(IRQTF_FORCED_THREAD, &new->thread_flags);
	new->thread_fn = new->handler;
	new->handler = irq_default_primary_handler;
	return 0;
}