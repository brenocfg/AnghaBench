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
struct pinctrl_dev {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int aspeed_pin_config_get (struct pinctrl_dev*,unsigned int const,unsigned long*) ; 
 int aspeed_pinctrl_get_group_pins (struct pinctrl_dev*,unsigned int,unsigned int const**,unsigned int*) ; 

int aspeed_pin_config_group_get(struct pinctrl_dev *pctldev,
		unsigned int selector,
		unsigned long *config)
{
	const unsigned int *pins;
	unsigned int npins;
	int rc;

	rc = aspeed_pinctrl_get_group_pins(pctldev, selector, &pins, &npins);
	if (rc < 0)
		return rc;

	if (!npins)
		return -ENODEV;

	rc = aspeed_pin_config_get(pctldev, pins[0], config);

	return rc;
}