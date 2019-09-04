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
struct axp20x_pctl {TYPE_1__* desc; } ;
struct TYPE_2__ {int npins; } ;

/* Variables and functions */
 struct axp20x_pctl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int axp20x_groups_cnt(struct pinctrl_dev *pctldev)
{
	struct axp20x_pctl *pctl = pinctrl_dev_get_drvdata(pctldev);

	return pctl->desc->npins;
}