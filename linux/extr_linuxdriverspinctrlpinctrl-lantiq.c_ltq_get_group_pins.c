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
struct pinctrl_dev {int dummy; } ;
struct ltq_pinmux_info {unsigned int num_grps; TYPE_1__* grps; } ;
struct TYPE_2__ {unsigned int* pins; unsigned int npins; } ;

/* Variables and functions */
 int EINVAL ; 
 struct ltq_pinmux_info* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int ltq_get_group_pins(struct pinctrl_dev *pctrldev,
				 unsigned selector,
				 const unsigned **pins,
				 unsigned *num_pins)
{
	struct ltq_pinmux_info *info = pinctrl_dev_get_drvdata(pctrldev);
	if (selector >= info->num_grps)
		return -EINVAL;
	*pins = info->grps[selector].pins;
	*num_pins = info->grps[selector].npins;
	return 0;
}