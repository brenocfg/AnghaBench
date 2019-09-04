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
struct byt_pingroup {scalar_t__ has_simple_funcs; } ;
struct byt_gpio {TYPE_1__* soc_data; } ;
struct byt_function {int /*<<< orphan*/  name; } ;
struct TYPE_2__ {struct byt_pingroup* groups; struct byt_function* functions; } ;

/* Variables and functions */
 unsigned short BYT_DEFAULT_GPIO_MUX ; 
 int byt_get_group_mixed_mux (struct byt_pingroup const,int /*<<< orphan*/ ,unsigned short const**) ; 
 int byt_get_group_simple_mux (struct byt_pingroup const,int /*<<< orphan*/ ,unsigned short*) ; 
 int /*<<< orphan*/  byt_set_group_mixed_mux (struct byt_gpio*,struct byt_pingroup const,unsigned short const*) ; 
 int /*<<< orphan*/  byt_set_group_simple_mux (struct byt_gpio*,struct byt_pingroup const,unsigned short) ; 
 struct byt_gpio* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int byt_set_mux(struct pinctrl_dev *pctldev, unsigned int func_selector,
		       unsigned int group_selector)
{
	struct byt_gpio *vg = pinctrl_dev_get_drvdata(pctldev);
	const struct byt_function func = vg->soc_data->functions[func_selector];
	const struct byt_pingroup group = vg->soc_data->groups[group_selector];
	const unsigned short *mixed_func;
	unsigned short simple_func;
	int ret = 1;

	if (group.has_simple_funcs)
		ret = byt_get_group_simple_mux(group, func.name, &simple_func);
	else
		ret = byt_get_group_mixed_mux(group, func.name, &mixed_func);

	if (ret)
		byt_set_group_simple_mux(vg, group, BYT_DEFAULT_GPIO_MUX);
	else if (group.has_simple_funcs)
		byt_set_group_simple_mux(vg, group, simple_func);
	else
		byt_set_group_mixed_mux(vg, group, mixed_func);

	return 0;
}