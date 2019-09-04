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
struct irqaction {int /*<<< orphan*/  percpu_dev_id; int /*<<< orphan*/  (* handler ) (unsigned int,int /*<<< orphan*/ ) ;} ;
struct irq_desc {int /*<<< orphan*/  irq_data; int /*<<< orphan*/  percpu_enabled; struct irqaction* action; } ;
struct irq_chip {int /*<<< orphan*/  (* irq_eoi ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* irq_ack ) (int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  __kstat_incr_irqs_this_cpu (struct irq_desc*) ; 
 int cpumask_test_cpu (unsigned int,int /*<<< orphan*/ ) ; 
 struct irq_chip* irq_desc_get_chip (struct irq_desc*) ; 
 unsigned int irq_desc_get_irq (struct irq_desc*) ; 
 int /*<<< orphan*/  irq_percpu_disable (struct irq_desc*,unsigned int) ; 
 scalar_t__ likely (struct irqaction*) ; 
 int /*<<< orphan*/  pr_err_once (char*,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  raw_cpu_ptr (int /*<<< orphan*/ ) ; 
 unsigned int smp_processor_id () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_irq_handler_entry (unsigned int,struct irqaction*) ; 
 int /*<<< orphan*/  trace_irq_handler_exit (unsigned int,struct irqaction*,int /*<<< orphan*/ ) ; 

void handle_percpu_devid_irq(struct irq_desc *desc)
{
	struct irq_chip *chip = irq_desc_get_chip(desc);
	struct irqaction *action = desc->action;
	unsigned int irq = irq_desc_get_irq(desc);
	irqreturn_t res;

	/*
	 * PER CPU interrupts are not serialized. Do not touch
	 * desc->tot_count.
	 */
	__kstat_incr_irqs_this_cpu(desc);

	if (chip->irq_ack)
		chip->irq_ack(&desc->irq_data);

	if (likely(action)) {
		trace_irq_handler_entry(irq, action);
		res = action->handler(irq, raw_cpu_ptr(action->percpu_dev_id));
		trace_irq_handler_exit(irq, action, res);
	} else {
		unsigned int cpu = smp_processor_id();
		bool enabled = cpumask_test_cpu(cpu, desc->percpu_enabled);

		if (enabled)
			irq_percpu_disable(desc, cpu);

		pr_err_once("Spurious%s percpu IRQ%u on CPU%u\n",
			    enabled ? " and unmasked" : "", irq, cpu);
	}

	if (chip->irq_eoi)
		chip->irq_eoi(&desc->irq_data);
}