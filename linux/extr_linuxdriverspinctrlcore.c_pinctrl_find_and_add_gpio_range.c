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
 int /*<<< orphan*/  EPROBE_DEFER ; 
 struct pinctrl_dev* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct pinctrl_dev* get_pinctrl_dev_from_devname (char const*) ; 
 int /*<<< orphan*/  pinctrl_add_gpio_range (struct pinctrl_dev*,struct pinctrl_gpio_range*) ; 

struct pinctrl_dev *pinctrl_find_and_add_gpio_range(const char *devname,
		struct pinctrl_gpio_range *range)
{
	struct pinctrl_dev *pctldev;

	pctldev = get_pinctrl_dev_from_devname(devname);

	/*
	 * If we can't find this device, let's assume that is because
	 * it has not probed yet, so the driver trying to register this
	 * range need to defer probing.
	 */
	if (!pctldev) {
		return ERR_PTR(-EPROBE_DEFER);
	}
	pinctrl_add_gpio_range(pctldev, range);

	return pctldev;
}