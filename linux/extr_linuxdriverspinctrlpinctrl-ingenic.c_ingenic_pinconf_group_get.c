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
 int ENOTSUPP ; 
 scalar_t__ ingenic_pinconf_get (struct pinctrl_dev*,unsigned int const,unsigned long*) ; 
 int pinctrl_generic_get_group_pins (struct pinctrl_dev*,unsigned int,unsigned int const**,unsigned int*) ; 

__attribute__((used)) static int ingenic_pinconf_group_get(struct pinctrl_dev *pctldev,
		unsigned int group, unsigned long *config)
{
	const unsigned int *pins;
	unsigned int i, npins, old = 0;
	int ret;

	ret = pinctrl_generic_get_group_pins(pctldev, group, &pins, &npins);
	if (ret)
		return ret;

	for (i = 0; i < npins; i++) {
		if (ingenic_pinconf_get(pctldev, pins[i], config))
			return -ENOTSUPP;

		/* configs do not match between two pins */
		if (i && (old != *config))
			return -ENOTSUPP;

		old = *config;
	}

	return 0;
}