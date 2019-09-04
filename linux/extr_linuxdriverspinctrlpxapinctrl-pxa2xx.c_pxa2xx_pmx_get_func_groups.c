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
struct pxa_pinctrl_function {char** groups; unsigned int ngroups; } ;
struct pxa_pinctrl {struct pxa_pinctrl_function* functions; } ;
struct pinctrl_dev {int dummy; } ;

/* Variables and functions */
 struct pxa_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int pxa2xx_pmx_get_func_groups(struct pinctrl_dev *pctldev,
				      unsigned function,
				      const char * const **groups,
				      unsigned * const num_groups)
{
	struct pxa_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	struct pxa_pinctrl_function *pf = pctl->functions + function;

	*groups = pf->groups;
	*num_groups = pf->ngroups;

	return 0;
}