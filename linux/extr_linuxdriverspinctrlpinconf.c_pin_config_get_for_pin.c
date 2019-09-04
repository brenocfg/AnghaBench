#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pinctrl_dev {int /*<<< orphan*/  dev; TYPE_1__* desc; } ;
struct pinconf_ops {int (* pin_config_get ) (struct pinctrl_dev*,unsigned int,unsigned long*) ;} ;
struct TYPE_2__ {struct pinconf_ops* confops; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int stub1 (struct pinctrl_dev*,unsigned int,unsigned long*) ; 

int pin_config_get_for_pin(struct pinctrl_dev *pctldev, unsigned pin,
			   unsigned long *config)
{
	const struct pinconf_ops *ops = pctldev->desc->confops;

	if (!ops || !ops->pin_config_get) {
		dev_dbg(pctldev->dev,
			"cannot get pin configuration, .pin_config_get missing in driver\n");
		return -ENOTSUPP;
	}

	return ops->pin_config_get(pctldev, pin, config);
}