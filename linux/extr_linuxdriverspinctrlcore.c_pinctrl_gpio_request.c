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
struct pinctrl_gpio_range {int dummy; } ;
struct pinctrl_dev {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int gpio_to_pin (struct pinctrl_gpio_range*,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pinctrl_get_device_gpio_range (unsigned int,struct pinctrl_dev**,struct pinctrl_gpio_range**) ; 
 scalar_t__ pinctrl_ready_for_gpio_range (unsigned int) ; 
 int pinmux_request_gpio (struct pinctrl_dev*,struct pinctrl_gpio_range*,int,unsigned int) ; 

int pinctrl_gpio_request(unsigned gpio)
{
	struct pinctrl_dev *pctldev;
	struct pinctrl_gpio_range *range;
	int ret;
	int pin;

	ret = pinctrl_get_device_gpio_range(gpio, &pctldev, &range);
	if (ret) {
		if (pinctrl_ready_for_gpio_range(gpio))
			ret = 0;
		return ret;
	}

	mutex_lock(&pctldev->mutex);

	/* Convert to the pin controllers number space */
	pin = gpio_to_pin(range, gpio);

	ret = pinmux_request_gpio(pctldev, range, pin, gpio);

	mutex_unlock(&pctldev->mutex);

	return ret;
}