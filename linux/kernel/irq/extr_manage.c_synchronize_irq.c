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
struct irq_desc {int /*<<< orphan*/  threads_active; int /*<<< orphan*/  wait_for_threads; } ;

/* Variables and functions */
 int /*<<< orphan*/  __synchronize_hardirq (struct irq_desc*,int) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 struct irq_desc* irq_to_desc (unsigned int) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

void synchronize_irq(unsigned int irq)
{
	struct irq_desc *desc = irq_to_desc(irq);

	if (desc) {
		__synchronize_hardirq(desc, true);
		/*
		 * We made sure that no hardirq handler is
		 * running. Now verify that no threaded handlers are
		 * active.
		 */
		wait_event(desc->wait_for_threads,
			   !atomic_read(&desc->threads_active));
	}
}