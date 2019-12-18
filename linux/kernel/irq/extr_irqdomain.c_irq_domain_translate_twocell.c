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
struct irq_fwspec {int param_count; unsigned long* param; } ;
struct irq_domain {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int IRQ_TYPE_SENSE_MASK ; 
 scalar_t__ WARN_ON (int) ; 

int irq_domain_translate_twocell(struct irq_domain *d,
				 struct irq_fwspec *fwspec,
				 unsigned long *out_hwirq,
				 unsigned int *out_type)
{
	if (WARN_ON(fwspec->param_count < 2))
		return -EINVAL;
	*out_hwirq = fwspec->param[0];
	*out_type = fwspec->param[1] & IRQ_TYPE_SENSE_MASK;
	return 0;
}