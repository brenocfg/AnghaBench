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
struct irq_desc {int /*<<< orphan*/  lock; int /*<<< orphan*/  irq_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_relax () ; 
 int irqd_irq_inprogress (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void __synchronize_hardirq(struct irq_desc *desc)
{
	bool inprogress;

	do {
		unsigned long flags;

		/*
		 * Wait until we're out of the critical section.  This might
		 * give the wrong answer due to the lack of memory barriers.
		 */
		while (irqd_irq_inprogress(&desc->irq_data))
			cpu_relax();

		/* Ok, that indicated we're done: double-check carefully. */
		raw_spin_lock_irqsave(&desc->lock, flags);
		inprogress = irqd_irq_inprogress(&desc->irq_data);
		raw_spin_unlock_irqrestore(&desc->lock, flags);

		/* Oops, that failed? */
	} while (inprogress);
}