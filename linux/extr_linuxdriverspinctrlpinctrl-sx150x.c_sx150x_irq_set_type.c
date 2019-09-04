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
struct sx150x_pinctrl {int dummy; } ;
struct irq_data {unsigned int hwirq; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int IRQ_TYPE_EDGE_FALLING ; 
 unsigned int IRQ_TYPE_EDGE_RISING ; 
 unsigned int IRQ_TYPE_LEVEL_HIGH ; 
 unsigned int IRQ_TYPE_LEVEL_LOW ; 
 unsigned int SX150X_IRQ_TYPE_EDGE_FALLING ; 
 unsigned int SX150X_IRQ_TYPE_EDGE_RISING ; 
 struct sx150x_pinctrl* gpiochip_get_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  sx150x_irq_set_sense (struct sx150x_pinctrl*,unsigned int,unsigned int) ; 

__attribute__((used)) static int sx150x_irq_set_type(struct irq_data *d, unsigned int flow_type)
{
	struct sx150x_pinctrl *pctl =
			gpiochip_get_data(irq_data_get_irq_chip_data(d));
	unsigned int n, val = 0;

	if (flow_type & (IRQ_TYPE_LEVEL_HIGH | IRQ_TYPE_LEVEL_LOW))
		return -EINVAL;

	n = d->hwirq;

	if (flow_type & IRQ_TYPE_EDGE_RISING)
		val |= SX150X_IRQ_TYPE_EDGE_RISING;
	if (flow_type & IRQ_TYPE_EDGE_FALLING)
		val |= SX150X_IRQ_TYPE_EDGE_FALLING;

	sx150x_irq_set_sense(pctl, n, val);
	return 0;
}