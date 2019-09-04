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
struct stm32_pinctrl {int /*<<< orphan*/ * irqmux; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct stm32_gpio_bank {int /*<<< orphan*/  bank_ioport_nr; TYPE_1__ gpio_chip; } ;
struct irq_domain {struct stm32_gpio_bank* host_data; } ;
struct irq_data {size_t hwirq; } ;

/* Variables and functions */
 struct stm32_pinctrl* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_field_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stm32_gpio_domain_activate(struct irq_domain *d,
				      struct irq_data *irq_data, bool reserve)
{
	struct stm32_gpio_bank *bank = d->host_data;
	struct stm32_pinctrl *pctl = dev_get_drvdata(bank->gpio_chip.parent);

	regmap_field_write(pctl->irqmux[irq_data->hwirq], bank->bank_ioport_nr);
	return 0;
}