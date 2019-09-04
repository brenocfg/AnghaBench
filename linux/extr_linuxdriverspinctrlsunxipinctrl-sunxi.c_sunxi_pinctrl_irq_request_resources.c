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
struct sunxi_pinctrl {scalar_t__* irq_array; int /*<<< orphan*/  pctl_dev; int /*<<< orphan*/  dev; TYPE_1__* desc; int /*<<< orphan*/  chip; } ;
struct sunxi_desc_function {int /*<<< orphan*/  muxval; } ;
struct irq_data {size_t hwirq; } ;
struct TYPE_2__ {scalar_t__ pin_base; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int gpiochip_lock_as_irq (int /*<<< orphan*/ ,scalar_t__) ; 
 struct sunxi_pinctrl* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  irqd_to_hwirq (struct irq_data*) ; 
 struct sunxi_desc_function* sunxi_pinctrl_desc_find_function_by_pin (struct sunxi_pinctrl*,scalar_t__,char*) ; 
 int /*<<< orphan*/  sunxi_pmx_set (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sunxi_pinctrl_irq_request_resources(struct irq_data *d)
{
	struct sunxi_pinctrl *pctl = irq_data_get_irq_chip_data(d);
	struct sunxi_desc_function *func;
	int ret;

	func = sunxi_pinctrl_desc_find_function_by_pin(pctl,
					pctl->irq_array[d->hwirq], "irq");
	if (!func)
		return -EINVAL;

	ret = gpiochip_lock_as_irq(pctl->chip,
			pctl->irq_array[d->hwirq] - pctl->desc->pin_base);
	if (ret) {
		dev_err(pctl->dev, "unable to lock HW IRQ %lu for IRQ\n",
			irqd_to_hwirq(d));
		return ret;
	}

	/* Change muxing to INT mode */
	sunxi_pmx_set(pctl->pctl_dev, pctl->irq_array[d->hwirq], func->muxval);

	return 0;
}