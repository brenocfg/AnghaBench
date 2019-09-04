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
struct sprd_pinctrl_soc_info {TYPE_1__* groups; } ;
struct sprd_pinctrl {struct sprd_pinctrl_soc_info* info; } ;
struct pinctrl_dev {int dummy; } ;
struct TYPE_2__ {char const* name; } ;

/* Variables and functions */
 struct sprd_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static const char *sprd_pctrl_group_name(struct pinctrl_dev *pctldev,
					 unsigned int selector)
{
	struct sprd_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	struct sprd_pinctrl_soc_info *info = pctl->info;

	return info->groups[selector].name;
}