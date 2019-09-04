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
 int /*<<< orphan*/  kfree (char const*) ; 
 char* pin_free (struct pinctrl_dev*,unsigned int,struct pinctrl_gpio_range*) ; 

void pinmux_free_gpio(struct pinctrl_dev *pctldev, unsigned pin,
		      struct pinctrl_gpio_range *range)
{
	const char *owner;

	owner = pin_free(pctldev, pin, range);
	kfree(owner);
}