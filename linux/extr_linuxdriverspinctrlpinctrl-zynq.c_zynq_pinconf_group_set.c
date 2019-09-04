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
struct zynq_pinctrl {struct zynq_pctrl_group* groups; } ;
struct zynq_pctrl_group {int npins; int /*<<< orphan*/ * pins; } ;
struct pinctrl_dev {int dummy; } ;

/* Variables and functions */
 struct zynq_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int zynq_pinconf_cfg_set (struct pinctrl_dev*,int /*<<< orphan*/ ,unsigned long*,unsigned int) ; 

__attribute__((used)) static int zynq_pinconf_group_set(struct pinctrl_dev *pctldev,
				  unsigned int selector,
				  unsigned long *configs,
				  unsigned int  num_configs)
{
	int i, ret;
	struct zynq_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);
	const struct zynq_pctrl_group *pgrp = &pctrl->groups[selector];

	for (i = 0; i < pgrp->npins; i++) {
		ret = zynq_pinconf_cfg_set(pctldev, pgrp->pins[i], configs,
					   num_configs);
		if (ret)
			return ret;
	}

	return 0;
}