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
struct sci_port {int* irqs; int /*<<< orphan*/ * irqstr; } ;

/* Variables and functions */
 scalar_t__ SCIx_IRQ_IS_MUXED (struct sci_port*) ; 
 int SCIx_NR_IRQS ; 
 int /*<<< orphan*/  free_irq (int,struct sci_port*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void sci_free_irq(struct sci_port *port)
{
	int i, j;

	/*
	 * Intentionally in reverse order so we iterate over the muxed
	 * IRQ first.
	 */
	for (i = 0; i < SCIx_NR_IRQS; i++) {
		int irq = port->irqs[i];

		/*
		 * Certain port types won't support all of the available
		 * interrupt sources.
		 */
		if (unlikely(irq < 0))
			continue;

		/* Check if already freed (irq was muxed) */
		for (j = 0; j < i; j++)
			if (port->irqs[j] == irq)
				j = i + 1;
		if (j > i)
			continue;

		free_irq(port->irqs[i], port);
		kfree(port->irqstr[i]);

		if (SCIx_IRQ_IS_MUXED(port)) {
			/* If there's only one IRQ, we're done. */
			return;
		}
	}
}