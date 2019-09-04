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
typedef  scalar_t__ irqreturn_t ;

/* Variables and functions */
 scalar_t__ IRQ_NONE ; 
 scalar_t__ wm8996_irq (int,void*) ; 

__attribute__((used)) static irqreturn_t wm8996_edge_irq(int irq, void *data)
{
	irqreturn_t ret = IRQ_NONE;
	irqreturn_t val;

	do {
		val = wm8996_irq(irq, data);
		if (val != IRQ_NONE)
			ret = val;
	} while (val != IRQ_NONE);

	return ret;
}