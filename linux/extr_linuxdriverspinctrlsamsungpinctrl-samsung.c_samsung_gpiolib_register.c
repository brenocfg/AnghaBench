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
struct samsung_pinctrl_drv_data {int nr_banks; struct samsung_pin_bank* pin_banks; } ;
struct TYPE_2__ {int /*<<< orphan*/  base; } ;
struct gpio_chip {int /*<<< orphan*/  label; int /*<<< orphan*/  of_node; int /*<<< orphan*/ * parent; int /*<<< orphan*/  ngpio; int /*<<< orphan*/  base; } ;
struct samsung_pin_bank {int /*<<< orphan*/  name; int /*<<< orphan*/  of_node; int /*<<< orphan*/  nr_pins; TYPE_1__ grange; struct gpio_chip gpio_chip; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int devm_gpiochip_add_data (int /*<<< orphan*/ *,struct gpio_chip*,struct samsung_pin_bank*) ; 
 struct gpio_chip samsung_gpiolib_chip ; 

__attribute__((used)) static int samsung_gpiolib_register(struct platform_device *pdev,
				    struct samsung_pinctrl_drv_data *drvdata)
{
	struct samsung_pin_bank *bank = drvdata->pin_banks;
	struct gpio_chip *gc;
	int ret;
	int i;

	for (i = 0; i < drvdata->nr_banks; ++i, ++bank) {
		bank->gpio_chip = samsung_gpiolib_chip;

		gc = &bank->gpio_chip;
		gc->base = bank->grange.base;
		gc->ngpio = bank->nr_pins;
		gc->parent = &pdev->dev;
		gc->of_node = bank->of_node;
		gc->label = bank->name;

		ret = devm_gpiochip_add_data(&pdev->dev, gc, bank);
		if (ret) {
			dev_err(&pdev->dev, "failed to register gpio_chip %s, error code: %d\n",
							gc->label, ret);
			return ret;
		}
	}

	return 0;
}