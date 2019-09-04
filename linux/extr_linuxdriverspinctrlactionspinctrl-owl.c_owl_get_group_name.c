#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pinctrl_dev {int dummy; } ;
struct owl_pinctrl {TYPE_2__* soc; } ;
struct TYPE_4__ {TYPE_1__* groups; } ;
struct TYPE_3__ {char const* name; } ;

/* Variables and functions */
 struct owl_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static const char *owl_get_group_name(struct pinctrl_dev *pctrldev,
				unsigned int group)
{
	struct owl_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctrldev);

	return pctrl->soc->groups[group].name;
}