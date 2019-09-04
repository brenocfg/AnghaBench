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
struct samsung_pinctrl_drv_data {unsigned int nr_banks; int /*<<< orphan*/  irq; struct samsung_pin_bank* pin_banks; struct device* dev; } ;
struct samsung_pin_bank {scalar_t__ eint_type; unsigned int eint_mask; scalar_t__ irq_domain; int /*<<< orphan*/  of_node; } ;
struct s3c64xx_eint_gpio_data {scalar_t__* domains; struct samsung_pinctrl_drv_data* drvdata; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ EINT_TYPE_GPIO ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct s3c64xx_eint_gpio_data* devm_kzalloc (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  domains ; 
 unsigned int fls (unsigned int) ; 
 scalar_t__ irq_domain_add_linear (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *,struct samsung_pin_bank*) ; 
 int /*<<< orphan*/  irq_set_chained_handler_and_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct s3c64xx_eint_gpio_data*) ; 
 int /*<<< orphan*/  s3c64xx_eint_gpio_irq ; 
 int /*<<< orphan*/  s3c64xx_gpio_irqd_ops ; 
 int /*<<< orphan*/  struct_size (struct s3c64xx_eint_gpio_data*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int s3c64xx_eint_gpio_init(struct samsung_pinctrl_drv_data *d)
{
	struct s3c64xx_eint_gpio_data *data;
	struct samsung_pin_bank *bank;
	struct device *dev = d->dev;
	unsigned int nr_domains;
	unsigned int i;

	if (!d->irq) {
		dev_err(dev, "irq number not available\n");
		return -EINVAL;
	}

	nr_domains = 0;
	bank = d->pin_banks;
	for (i = 0; i < d->nr_banks; ++i, ++bank) {
		unsigned int nr_eints;
		unsigned int mask;

		if (bank->eint_type != EINT_TYPE_GPIO)
			continue;

		mask = bank->eint_mask;
		nr_eints = fls(mask);

		bank->irq_domain = irq_domain_add_linear(bank->of_node,
					nr_eints, &s3c64xx_gpio_irqd_ops, bank);
		if (!bank->irq_domain) {
			dev_err(dev, "gpio irq domain add failed\n");
			return -ENXIO;
		}

		++nr_domains;
	}

	data = devm_kzalloc(dev, struct_size(data, domains, nr_domains),
			    GFP_KERNEL);
	if (!data)
		return -ENOMEM;
	data->drvdata = d;

	bank = d->pin_banks;
	nr_domains = 0;
	for (i = 0; i < d->nr_banks; ++i, ++bank) {
		if (bank->eint_type != EINT_TYPE_GPIO)
			continue;

		data->domains[nr_domains++] = bank->irq_domain;
	}

	irq_set_chained_handler_and_data(d->irq, s3c64xx_eint_gpio_irq, data);

	return 0;
}