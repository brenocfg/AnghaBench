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
struct irq_desc {scalar_t__ depth; } ;
struct irq_data {int dummy; } ;
struct cpumask {int dummy; } ;

/* Variables and functions */
#define  IRQ_STARTUP_ABORT 130 
#define  IRQ_STARTUP_MANAGED 129 
#define  IRQ_STARTUP_NORMAL 128 
 int __irq_startup (struct irq_desc*) ; 
 int __irq_startup_managed (struct irq_desc*,struct cpumask*,int) ; 
 int /*<<< orphan*/  check_irq_resend (struct irq_desc*) ; 
 struct cpumask* irq_data_get_affinity_mask (struct irq_data*) ; 
 struct irq_data* irq_desc_get_irq_data (struct irq_desc*) ; 
 int /*<<< orphan*/  irq_do_set_affinity (struct irq_data*,struct cpumask*,int) ; 
 int /*<<< orphan*/  irq_enable (struct irq_desc*) ; 
 int /*<<< orphan*/  irq_setup_affinity (struct irq_desc*) ; 
 scalar_t__ irqd_is_started (struct irq_data*) ; 
 int /*<<< orphan*/  irqd_set_managed_shutdown (struct irq_data*) ; 

int irq_startup(struct irq_desc *desc, bool resend, bool force)
{
	struct irq_data *d = irq_desc_get_irq_data(desc);
	struct cpumask *aff = irq_data_get_affinity_mask(d);
	int ret = 0;

	desc->depth = 0;

	if (irqd_is_started(d)) {
		irq_enable(desc);
	} else {
		switch (__irq_startup_managed(desc, aff, force)) {
		case IRQ_STARTUP_NORMAL:
			ret = __irq_startup(desc);
			irq_setup_affinity(desc);
			break;
		case IRQ_STARTUP_MANAGED:
			irq_do_set_affinity(d, aff, false);
			ret = __irq_startup(desc);
			break;
		case IRQ_STARTUP_ABORT:
			irqd_set_managed_shutdown(d);
			return 0;
		}
	}
	if (resend)
		check_irq_resend(desc);

	return ret;
}