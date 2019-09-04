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
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct pinctrl_gpio_range* pinctrl_find_gpio_range_from_pin_nolock (struct pinctrl_dev*,unsigned int) ; 

struct pinctrl_gpio_range *
pinctrl_find_gpio_range_from_pin(struct pinctrl_dev *pctldev,
				 unsigned int pin)
{
	struct pinctrl_gpio_range *range;

	mutex_lock(&pctldev->mutex);
	range = pinctrl_find_gpio_range_from_pin_nolock(pctldev, pin);
	mutex_unlock(&pctldev->mutex);

	return range;
}