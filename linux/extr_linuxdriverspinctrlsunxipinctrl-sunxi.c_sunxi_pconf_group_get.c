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
struct sunxi_pinctrl_group {int /*<<< orphan*/  pin; } ;
struct sunxi_pinctrl {struct sunxi_pinctrl_group* groups; } ;
struct pinctrl_dev {int dummy; } ;

/* Variables and functions */
 struct sunxi_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int sunxi_pconf_get (struct pinctrl_dev*,int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static int sunxi_pconf_group_get(struct pinctrl_dev *pctldev,
				 unsigned group,
				 unsigned long *config)
{
	struct sunxi_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	struct sunxi_pinctrl_group *g = &pctl->groups[group];

	/* We only support 1 pin per group. Chain it to the pin callback */
	return sunxi_pconf_get(pctldev, g->pin, config);
}