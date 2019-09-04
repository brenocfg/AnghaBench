#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sunxi_pinctrl {TYPE_1__* desc; } ;
struct sunxi_desc_function {int const irqbank; int const irqnum; } ;
struct irq_domain {struct sunxi_pinctrl* host_data; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {int pin_base; } ;

/* Variables and functions */
 int EINVAL ; 
 int const PINS_PER_BANK ; 
 struct sunxi_desc_function* sunxi_pinctrl_desc_find_function_by_pin (struct sunxi_pinctrl*,int,char*) ; 

__attribute__((used)) static int sunxi_pinctrl_irq_of_xlate(struct irq_domain *d,
				      struct device_node *node,
				      const u32 *intspec,
				      unsigned int intsize,
				      unsigned long *out_hwirq,
				      unsigned int *out_type)
{
	struct sunxi_pinctrl *pctl = d->host_data;
	struct sunxi_desc_function *desc;
	int pin, base;

	if (intsize < 3)
		return -EINVAL;

	base = PINS_PER_BANK * intspec[0];
	pin = pctl->desc->pin_base + base + intspec[1];

	desc = sunxi_pinctrl_desc_find_function_by_pin(pctl, pin, "irq");
	if (!desc)
		return -EINVAL;

	*out_hwirq = desc->irqbank * PINS_PER_BANK + desc->irqnum;
	*out_type = intspec[2];

	return 0;
}