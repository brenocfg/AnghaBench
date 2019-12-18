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
struct irq_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ack_bad_irq (unsigned int) ; 
 unsigned int irq_desc_get_irq (struct irq_desc*) ; 
 int /*<<< orphan*/  kstat_incr_irqs_this_cpu (struct irq_desc*) ; 
 int /*<<< orphan*/  print_irq_desc (unsigned int,struct irq_desc*) ; 

void handle_bad_irq(struct irq_desc *desc)
{
	unsigned int irq = irq_desc_get_irq(desc);

	print_irq_desc(irq, desc);
	kstat_incr_irqs_this_cpu(desc);
	ack_bad_irq(irq);
}