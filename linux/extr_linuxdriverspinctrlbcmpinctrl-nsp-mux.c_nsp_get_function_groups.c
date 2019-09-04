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
struct nsp_pinctrl {TYPE_1__* functions; } ;
struct TYPE_2__ {char** groups; unsigned int num_groups; } ;

/* Variables and functions */
 struct nsp_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int nsp_get_function_groups(struct pinctrl_dev *pctrl_dev,
				   unsigned int selector,
				   const char * const **groups,
				   unsigned * const num_groups)
{
	struct nsp_pinctrl *pinctrl = pinctrl_dev_get_drvdata(pctrl_dev);

	*groups = pinctrl->functions[selector].groups;
	*num_groups = pinctrl->functions[selector].num_groups;

	return 0;
}