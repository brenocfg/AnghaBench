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
struct atmel_pioctrl {char** group_names; unsigned int npins; } ;

/* Variables and functions */
 struct atmel_pioctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int atmel_pmx_get_function_groups(struct pinctrl_dev *pctldev,
					 unsigned selector,
					 const char * const **groups,
					 unsigned * const num_groups)
{
	struct atmel_pioctrl *atmel_pioctrl = pinctrl_dev_get_drvdata(pctldev);

	*groups = atmel_pioctrl->group_names;
	*num_groups = atmel_pioctrl->npins;

	return 0;
}