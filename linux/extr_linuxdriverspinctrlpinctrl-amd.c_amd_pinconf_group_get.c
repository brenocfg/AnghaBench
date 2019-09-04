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
 int amd_get_group_pins (struct pinctrl_dev*,unsigned int,unsigned int const**,unsigned int*) ; 
 scalar_t__ amd_pinconf_get (struct pinctrl_dev*,unsigned int const,unsigned long*) ; 

__attribute__((used)) static int amd_pinconf_group_get(struct pinctrl_dev *pctldev,
				unsigned int group,
				unsigned long *config)
{
	const unsigned *pins;
	unsigned npins;
	int ret;

	ret = amd_get_group_pins(pctldev, group, &pins, &npins);
	if (ret)
		return ret;

	if (amd_pinconf_get(pctldev, pins[0], config))
			return -ENOTSUPP;

	return 0;
}