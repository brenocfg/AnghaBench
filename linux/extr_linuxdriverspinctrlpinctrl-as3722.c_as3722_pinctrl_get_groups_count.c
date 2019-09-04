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
struct pinctrl_dev {int dummy; } ;
struct as3722_pctrl_info {int num_pin_groups; } ;

/* Variables and functions */
 struct as3722_pctrl_info* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int as3722_pinctrl_get_groups_count(struct pinctrl_dev *pctldev)
{
	struct as3722_pctrl_info *as_pci = pinctrl_dev_get_drvdata(pctldev);

	return as_pci->num_pin_groups;
}