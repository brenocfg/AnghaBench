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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct gpio_keys_platform_data {int nbuttons; struct gpio_keys_button* buttons; } ;
struct gpio_keys_button_dev {struct gpio_keys_button_data* data; struct gpio_keys_platform_data* pdata; } ;
struct gpio_keys_button_data {scalar_t__ irq; int /*<<< orphan*/  software_debounce; int /*<<< orphan*/  work; int /*<<< orphan*/  gpiod; } ;
struct gpio_keys_button {scalar_t__ irq; int /*<<< orphan*/  gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned long IRQF_ONESHOT ; 
 unsigned long IRQF_TRIGGER_FALLING ; 
 unsigned long IRQF_TRIGGER_RISING ; 
 int /*<<< orphan*/  button_handle_irq ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,struct gpio_keys_button_data*) ; 
 int gpio_keys_button_probe (struct platform_device*,struct gpio_keys_button_dev**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_keys_irq_work_func ; 
 scalar_t__ gpio_to_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gpio_keys_probe(struct platform_device *pdev)
{
	struct gpio_keys_platform_data *pdata;
	struct gpio_keys_button_dev *bdev;
	int ret, i;


	ret = gpio_keys_button_probe(pdev, &bdev, 0);

	if (ret)
		return ret;

	pdata = bdev->pdata;
	for (i = 0; i < pdata->nbuttons; i++) {
		const struct gpio_keys_button *button = &pdata->buttons[i];
		struct gpio_keys_button_data *bdata = &bdev->data[i];
		unsigned long irqflags = IRQF_ONESHOT;

		INIT_DELAYED_WORK(&bdata->work, gpio_keys_irq_work_func);

		if (!bdata->gpiod)
			continue;

		if (!button->irq) {
			bdata->irq = gpio_to_irq(button->gpio);

			if (bdata->irq < 0) {
				dev_err(&pdev->dev, "failed to get irq for gpio:%d\n",
					button->gpio);
				continue;
			}

			irqflags |= IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING;
		} else {
			bdata->irq = button->irq;
		}

		schedule_delayed_work(&bdata->work,
				      msecs_to_jiffies(bdata->software_debounce));

		ret = devm_request_threaded_irq(&pdev->dev,
			bdata->irq, NULL, button_handle_irq,
			irqflags, dev_name(&pdev->dev), bdata);

		if (ret < 0) {
			bdata->irq = 0;
			dev_err(&pdev->dev, "failed to request irq:%d for gpio:%d\n",
				bdata->irq, button->gpio);
			continue;
		} else {
			dev_dbg(&pdev->dev, "gpio:%d has irq:%d\n",
				button->gpio, bdata->irq);
		}
	}

	return 0;
}