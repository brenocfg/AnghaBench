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
struct st_pinctrl {TYPE_1__* functions; } ;
struct pinctrl_dev {int dummy; } ;
struct TYPE_2__ {char** groups; unsigned int ngroups; } ;

/* Variables and functions */
 struct st_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int st_pmx_get_groups(struct pinctrl_dev *pctldev,
	unsigned selector, const char * const **grps, unsigned * const ngrps)
{
	struct st_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);
	*grps = info->functions[selector].groups;
	*ngrps = info->functions[selector].ngroups;

	return 0;
}