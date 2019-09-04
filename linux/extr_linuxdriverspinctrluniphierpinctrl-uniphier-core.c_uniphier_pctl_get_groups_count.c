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
struct uniphier_pinctrl_priv {TYPE_1__* socdata; } ;
struct pinctrl_dev {int dummy; } ;
struct TYPE_2__ {int groups_count; } ;

/* Variables and functions */
 struct uniphier_pinctrl_priv* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int uniphier_pctl_get_groups_count(struct pinctrl_dev *pctldev)
{
	struct uniphier_pinctrl_priv *priv = pinctrl_dev_get_drvdata(pctldev);

	return priv->socdata->groups_count;
}