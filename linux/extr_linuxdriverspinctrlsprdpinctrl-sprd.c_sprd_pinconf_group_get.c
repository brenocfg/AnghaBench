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
struct sprd_pinctrl_soc_info {unsigned int ngroups; struct sprd_pin_group* groups; } ;
struct sprd_pinctrl {struct sprd_pinctrl_soc_info* info; } ;
struct sprd_pin_group {unsigned int* pins; } ;
struct pinctrl_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct sprd_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int sprd_pinconf_get (struct pinctrl_dev*,unsigned int,unsigned long*) ; 

__attribute__((used)) static int sprd_pinconf_group_get(struct pinctrl_dev *pctldev,
				  unsigned int selector, unsigned long *config)
{
	struct sprd_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	struct sprd_pinctrl_soc_info *info = pctl->info;
	struct sprd_pin_group *grp;
	unsigned int pin_id;

	if (selector >= info->ngroups)
		return -EINVAL;

	grp = &info->groups[selector];
	pin_id = grp->pins[0];

	return sprd_pinconf_get(pctldev, pin_id, config);
}