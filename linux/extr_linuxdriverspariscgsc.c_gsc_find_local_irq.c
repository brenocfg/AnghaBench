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

/* Variables and functions */
 int NO_IRQ ; 

int gsc_find_local_irq(unsigned int irq, int *global_irqs, int limit)
{
	int local_irq;

	for (local_irq = 0; local_irq < limit; local_irq++) {
		if (global_irqs[local_irq] == irq)
			return local_irq;
	}

	return NO_IRQ;
}