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
struct pinctrl_dev {TYPE_1__* desc; } ;
struct TYPE_2__ {unsigned int npins; } ;

/* Variables and functions */
 char** pmic_mpp_groups ; 

__attribute__((used)) static int pmic_mpp_get_function_groups(struct pinctrl_dev *pctldev,
					unsigned function,
					const char *const **groups,
					unsigned *const num_qgroups)
{
	*groups = pmic_mpp_groups;
	*num_qgroups = pctldev->desc->npins;
	return 0;
}