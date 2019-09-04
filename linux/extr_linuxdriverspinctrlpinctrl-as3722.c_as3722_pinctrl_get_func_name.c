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
struct as3722_pctrl_info {TYPE_1__* functions; } ;
struct TYPE_2__ {char const* name; } ;

/* Variables and functions */
 struct as3722_pctrl_info* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static const char *as3722_pinctrl_get_func_name(struct pinctrl_dev *pctldev,
			unsigned function)
{
	struct as3722_pctrl_info *as_pci = pinctrl_dev_get_drvdata(pctldev);

	return as_pci->functions[function].name;
}