#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct pinctrl_pin_desc {int number; int /*<<< orphan*/  name; } ;
struct at91_pinctrl {int nactive_banks; int /*<<< orphan*/  pctl; } ;
struct TYPE_5__ {int npins; struct pinctrl_pin_desc* pins; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  range; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int MAX_NB_GPIO_PER_BANK ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 TYPE_2__ at91_pinctrl_desc ; 
 int at91_pinctrl_probe_dt (struct platform_device*,struct at91_pinctrl*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int,int) ; 
 struct pinctrl_pin_desc* devm_kcalloc (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ *,struct at91_pinctrl*) ; 
 struct at91_pinctrl* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_pinctrl_register (int /*<<< orphan*/ *,TYPE_2__*,struct at91_pinctrl*) ; 
 int gpio_banks ; 
 TYPE_1__** gpio_chips ; 
 int /*<<< orphan*/  kasprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  pinctrl_add_gpio_range (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct at91_pinctrl*) ; 

__attribute__((used)) static int at91_pinctrl_probe(struct platform_device *pdev)
{
	struct at91_pinctrl *info;
	struct pinctrl_pin_desc *pdesc;
	int ret, i, j, k, ngpio_chips_enabled = 0;

	info = devm_kzalloc(&pdev->dev, sizeof(*info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	ret = at91_pinctrl_probe_dt(pdev, info);
	if (ret)
		return ret;

	/*
	 * We need all the GPIO drivers to probe FIRST, or we will not be able
	 * to obtain references to the struct gpio_chip * for them, and we
	 * need this to proceed.
	 */
	for (i = 0; i < gpio_banks; i++)
		if (gpio_chips[i])
			ngpio_chips_enabled++;

	if (ngpio_chips_enabled < info->nactive_banks) {
		dev_warn(&pdev->dev,
			 "All GPIO chips are not registered yet (%d/%d)\n",
			 ngpio_chips_enabled, info->nactive_banks);
		devm_kfree(&pdev->dev, info);
		return -EPROBE_DEFER;
	}

	at91_pinctrl_desc.name = dev_name(&pdev->dev);
	at91_pinctrl_desc.npins = gpio_banks * MAX_NB_GPIO_PER_BANK;
	at91_pinctrl_desc.pins = pdesc =
		devm_kcalloc(&pdev->dev,
			     at91_pinctrl_desc.npins, sizeof(*pdesc),
			     GFP_KERNEL);

	if (!at91_pinctrl_desc.pins)
		return -ENOMEM;

	for (i = 0, k = 0; i < gpio_banks; i++) {
		for (j = 0; j < MAX_NB_GPIO_PER_BANK; j++, k++) {
			pdesc->number = k;
			pdesc->name = kasprintf(GFP_KERNEL, "pio%c%d", i + 'A', j);
			pdesc++;
		}
	}

	platform_set_drvdata(pdev, info);
	info->pctl = devm_pinctrl_register(&pdev->dev, &at91_pinctrl_desc,
					   info);

	if (IS_ERR(info->pctl)) {
		dev_err(&pdev->dev, "could not register AT91 pinctrl driver\n");
		return PTR_ERR(info->pctl);
	}

	/* We will handle a range of GPIO pins */
	for (i = 0; i < gpio_banks; i++)
		if (gpio_chips[i])
			pinctrl_add_gpio_range(info->pctl, &gpio_chips[i]->range);

	dev_info(&pdev->dev, "initialized AT91 pinctrl driver\n");

	return 0;
}