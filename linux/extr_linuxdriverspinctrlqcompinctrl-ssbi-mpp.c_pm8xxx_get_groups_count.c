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
struct pm8xxx_mpp {int npins; } ;
struct pinctrl_dev {int dummy; } ;

/* Variables and functions */
 struct pm8xxx_mpp* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int pm8xxx_get_groups_count(struct pinctrl_dev *pctldev)
{
	struct pm8xxx_mpp *pctrl = pinctrl_dev_get_drvdata(pctldev);

	return pctrl->npins;
}