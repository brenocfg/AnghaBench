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
struct ltc2952_poweroff {int /*<<< orphan*/ * gpio_trigger; int /*<<< orphan*/ * gpio_kill; int /*<<< orphan*/ * gpio_watchdog; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOD_IN ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 int IRQF_TRIGGER_FALLING ; 
 int IRQF_TRIGGER_RISING ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 void* devm_gpiod_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * devm_gpiod_get_optional (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_gpiod_put (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ devm_request_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,struct ltc2952_poweroff*) ; 
 int /*<<< orphan*/  gpiod_to_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ltc2952_poweroff_default (struct ltc2952_poweroff*) ; 
 int /*<<< orphan*/  ltc2952_poweroff_handler ; 
 int /*<<< orphan*/  ltc2952_poweroff_start_wde (struct ltc2952_poweroff*) ; 
 struct ltc2952_poweroff* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int ltc2952_poweroff_init(struct platform_device *pdev)
{
	int ret;
	struct ltc2952_poweroff *data = platform_get_drvdata(pdev);

	ltc2952_poweroff_default(data);

	data->gpio_watchdog = devm_gpiod_get(&pdev->dev, "watchdog",
					     GPIOD_OUT_LOW);
	if (IS_ERR(data->gpio_watchdog)) {
		ret = PTR_ERR(data->gpio_watchdog);
		dev_err(&pdev->dev, "unable to claim gpio \"watchdog\"\n");
		return ret;
	}

	data->gpio_kill = devm_gpiod_get(&pdev->dev, "kill", GPIOD_OUT_LOW);
	if (IS_ERR(data->gpio_kill)) {
		ret = PTR_ERR(data->gpio_kill);
		dev_err(&pdev->dev, "unable to claim gpio \"kill\"\n");
		return ret;
	}

	data->gpio_trigger = devm_gpiod_get_optional(&pdev->dev, "trigger",
						     GPIOD_IN);
	if (IS_ERR(data->gpio_trigger)) {
		/*
		 * It's not a problem if the trigger gpio isn't available, but
		 * it is worth a warning if its use was defined in the device
		 * tree.
		 */
		dev_err(&pdev->dev, "unable to claim gpio \"trigger\"\n");
		data->gpio_trigger = NULL;
	}

	if (devm_request_irq(&pdev->dev, gpiod_to_irq(data->gpio_trigger),
			     ltc2952_poweroff_handler,
			     (IRQF_TRIGGER_FALLING | IRQF_TRIGGER_RISING),
			     "ltc2952-poweroff",
			     data)) {
		/*
		 * Some things may have happened:
		 * - No trigger input was defined
		 * - Claiming the GPIO failed
		 * - We could not map to an IRQ
		 * - We couldn't register an interrupt handler
		 *
		 * None of these really are problems, but all of them
		 * disqualify the push button from controlling the power.
		 *
		 * It is therefore important to note that if the ltc2952
		 * detects a button press for long enough, it will still start
		 * its own powerdown window and cut the power on us if we don't
		 * start the watchdog trigger.
		 */
		if (data->gpio_trigger) {
			dev_warn(&pdev->dev,
				 "unable to configure the trigger interrupt\n");
			devm_gpiod_put(&pdev->dev, data->gpio_trigger);
			data->gpio_trigger = NULL;
		}
		dev_info(&pdev->dev,
			 "power down trigger input will not be used\n");
		ltc2952_poweroff_start_wde(data);
	}

	return 0;
}