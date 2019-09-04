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
struct mtk_pinctrl_group {int /*<<< orphan*/  pin; } ;
struct mtk_pinctrl {int /*<<< orphan*/  dev; struct mtk_pinctrl_group* groups; } ;
struct mtk_desc_function {int /*<<< orphan*/  muxval; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 struct mtk_desc_function* mtk_pctrl_find_function_by_pin (struct mtk_pinctrl*,int /*<<< orphan*/ ,unsigned int) ; 
 int mtk_pctrl_is_function_valid (struct mtk_pinctrl*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  mtk_pmx_set_mode (struct pinctrl_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mtk_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int mtk_pmx_set_mux(struct pinctrl_dev *pctldev,
			    unsigned function,
			    unsigned group)
{
	bool ret;
	const struct mtk_desc_function *desc;
	struct mtk_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	struct mtk_pinctrl_group *g = pctl->groups + group;

	ret = mtk_pctrl_is_function_valid(pctl, g->pin, function);
	if (!ret) {
		dev_err(pctl->dev, "invalid function %d on group %d .\n",
				function, group);
		return -EINVAL;
	}

	desc = mtk_pctrl_find_function_by_pin(pctl, g->pin, function);
	if (!desc)
		return -EINVAL;
	mtk_pmx_set_mode(pctldev, g->pin, desc->muxval);
	return 0;
}