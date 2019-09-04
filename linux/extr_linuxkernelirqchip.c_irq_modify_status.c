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
struct irq_desc {int /*<<< orphan*/  irq_data; int /*<<< orphan*/  depth; } ;

/* Variables and functions */
 unsigned long IRQD_LEVEL ; 
 unsigned long IRQD_MOVE_PCNTXT ; 
 unsigned long IRQD_NO_BALANCING ; 
 unsigned long IRQD_PER_CPU ; 
 unsigned long IRQD_TRIGGER_MASK ; 
 unsigned long IRQ_TYPE_NONE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 unsigned long _IRQ_NOAUTOEN ; 
 struct irq_desc* irq_get_desc_lock (unsigned int,unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_put_desc_unlock (struct irq_desc*,unsigned long) ; 
 scalar_t__ irq_settings_can_move_pcntxt (struct irq_desc*) ; 
 int /*<<< orphan*/  irq_settings_clr_and_set (struct irq_desc*,unsigned long,unsigned long) ; 
 unsigned long irq_settings_get_trigger_mask (struct irq_desc*) ; 
 scalar_t__ irq_settings_has_no_balance_set (struct irq_desc*) ; 
 scalar_t__ irq_settings_is_level (struct irq_desc*) ; 
 scalar_t__ irq_settings_is_per_cpu (struct irq_desc*) ; 
 int /*<<< orphan*/  irqd_clear (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long irqd_get_trigger_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irqd_set (int /*<<< orphan*/ *,unsigned long) ; 

void irq_modify_status(unsigned int irq, unsigned long clr, unsigned long set)
{
	unsigned long flags, trigger, tmp;
	struct irq_desc *desc = irq_get_desc_lock(irq, &flags, 0);

	if (!desc)
		return;

	/*
	 * Warn when a driver sets the no autoenable flag on an already
	 * active interrupt.
	 */
	WARN_ON_ONCE(!desc->depth && (set & _IRQ_NOAUTOEN));

	irq_settings_clr_and_set(desc, clr, set);

	trigger = irqd_get_trigger_type(&desc->irq_data);

	irqd_clear(&desc->irq_data, IRQD_NO_BALANCING | IRQD_PER_CPU |
		   IRQD_TRIGGER_MASK | IRQD_LEVEL | IRQD_MOVE_PCNTXT);
	if (irq_settings_has_no_balance_set(desc))
		irqd_set(&desc->irq_data, IRQD_NO_BALANCING);
	if (irq_settings_is_per_cpu(desc))
		irqd_set(&desc->irq_data, IRQD_PER_CPU);
	if (irq_settings_can_move_pcntxt(desc))
		irqd_set(&desc->irq_data, IRQD_MOVE_PCNTXT);
	if (irq_settings_is_level(desc))
		irqd_set(&desc->irq_data, IRQD_LEVEL);

	tmp = irq_settings_get_trigger_mask(desc);
	if (tmp != IRQ_TYPE_NONE)
		trigger = tmp;

	irqd_set(&desc->irq_data, trigger);

	irq_put_desc_unlock(desc, flags);
}