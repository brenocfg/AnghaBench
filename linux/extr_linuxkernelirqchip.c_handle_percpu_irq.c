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
struct irq_desc {int /*<<< orphan*/  irq_data; } ;
struct irq_chip {int /*<<< orphan*/  (* irq_eoi ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* irq_ack ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  __kstat_incr_irqs_this_cpu (struct irq_desc*) ; 
 int /*<<< orphan*/  handle_irq_event_percpu (struct irq_desc*) ; 
 struct irq_chip* irq_desc_get_chip (struct irq_desc*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 

void handle_percpu_irq(struct irq_desc *desc)
{
	struct irq_chip *chip = irq_desc_get_chip(desc);

	/*
	 * PER CPU interrupts are not serialized. Do not touch
	 * desc->tot_count.
	 */
	__kstat_incr_irqs_this_cpu(desc);

	if (chip->irq_ack)
		chip->irq_ack(&desc->irq_data);

	handle_irq_event_percpu(desc);

	if (chip->irq_eoi)
		chip->irq_eoi(&desc->irq_data);
}