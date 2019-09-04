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
struct rt2880_priv {char** group_names; TYPE_1__** func; } ;
struct pinctrl_dev {int dummy; } ;
struct TYPE_2__ {int group_count; size_t* groups; } ;

/* Variables and functions */
 struct rt2880_priv* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int rt2880_pmx_group_get_groups(struct pinctrl_dev *pctrldev,
				       unsigned int func,
				       const char * const **groups,
				       unsigned int * const num_groups)
{
	struct rt2880_priv *p = pinctrl_dev_get_drvdata(pctrldev);

	if (p->func[func]->group_count == 1)
		*groups = &p->group_names[p->func[func]->groups[0]];
	else
		*groups = p->group_names;

	*num_groups = p->func[func]->group_count;

	return 0;
}