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
struct lpc18xx_scu_data {TYPE_1__* func; } ;
struct TYPE_2__ {char** groups; unsigned int ngroups; } ;

/* Variables and functions */
 struct lpc18xx_scu_data* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int lpc18xx_pmx_get_func_groups(struct pinctrl_dev *pctldev,
				       unsigned function,
				       const char *const **groups,
				       unsigned *const num_groups)
{
	struct lpc18xx_scu_data *scu = pinctrl_dev_get_drvdata(pctldev);

	*groups  = scu->func[function].groups;
	*num_groups = scu->func[function].ngroups;

	return 0;
}