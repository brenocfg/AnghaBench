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
struct armada_37xx_pinctrl {unsigned int ngroups; TYPE_1__* groups; } ;
struct TYPE_2__ {unsigned int* pins; unsigned int npins; unsigned int extra_npins; } ;

/* Variables and functions */
 int EINVAL ; 
 struct armada_37xx_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int armada_37xx_get_group_pins(struct pinctrl_dev *pctldev,
				      unsigned int selector,
				      const unsigned int **pins,
				      unsigned int *npins)
{
	struct armada_37xx_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);

	if (selector >= info->ngroups)
		return -EINVAL;

	*pins = info->groups[selector].pins;
	*npins = info->groups[selector].npins +
		info->groups[selector].extra_npins;

	return 0;
}