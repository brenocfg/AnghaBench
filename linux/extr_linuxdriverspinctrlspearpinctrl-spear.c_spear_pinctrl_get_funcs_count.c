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
struct spear_pmx {TYPE_1__* machdata; } ;
struct pinctrl_dev {int dummy; } ;
struct TYPE_2__ {int nfunctions; } ;

/* Variables and functions */
 struct spear_pmx* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int spear_pinctrl_get_funcs_count(struct pinctrl_dev *pctldev)
{
	struct spear_pmx *pmx = pinctrl_dev_get_drvdata(pctldev);

	return pmx->machdata->nfunctions;
}