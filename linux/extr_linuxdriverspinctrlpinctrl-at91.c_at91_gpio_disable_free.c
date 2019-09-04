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
struct pinctrl_dev {int dummy; } ;
struct at91_pinctrl {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 struct at91_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static void at91_gpio_disable_free(struct pinctrl_dev *pctldev,
				   struct pinctrl_gpio_range *range,
				   unsigned offset)
{
	struct at91_pinctrl *npct = pinctrl_dev_get_drvdata(pctldev);

	dev_dbg(npct->dev, "disable pin %u as GPIO\n", offset);
	/* Set the pin to some default state, GPIO is usually default */
}