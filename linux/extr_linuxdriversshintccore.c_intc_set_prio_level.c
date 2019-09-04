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
 int /*<<< orphan*/  intc_big_lock ; 
 unsigned int* intc_prio_level ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void intc_set_prio_level(unsigned int irq, unsigned int level)
{
	unsigned long flags;

	raw_spin_lock_irqsave(&intc_big_lock, flags);
	intc_prio_level[irq] = level;
	raw_spin_unlock_irqrestore(&intc_big_lock, flags);
}