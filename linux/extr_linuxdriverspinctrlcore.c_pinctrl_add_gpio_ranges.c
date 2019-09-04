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

/* Variables and functions */
 int /*<<< orphan*/  pinctrl_add_gpio_range (struct pinctrl_dev*,struct pinctrl_gpio_range*) ; 

void pinctrl_add_gpio_ranges(struct pinctrl_dev *pctldev,
			     struct pinctrl_gpio_range *ranges,
			     unsigned nranges)
{
	int i;

	for (i = 0; i < nranges; i++)
		pinctrl_add_gpio_range(pctldev, &ranges[i]);
}