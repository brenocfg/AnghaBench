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
struct pinctrl_gpio_range {int dummy; } ;
struct pinctrl_dev {int dummy; } ;
struct mtk_pinctrl {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PIN_CONFIG_INPUT_ENABLE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  mtk_pconf_set_ies_smt (struct mtk_pinctrl*,unsigned int,int,int /*<<< orphan*/ ) ; 
 int mtk_pmx_find_gpio_mode (struct mtk_pinctrl*,unsigned int) ; 
 int /*<<< orphan*/  mtk_pmx_set_mode (struct pinctrl_dev*,unsigned int,int) ; 
 struct mtk_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int mtk_pmx_gpio_request_enable(struct pinctrl_dev *pctldev,
				    struct pinctrl_gpio_range *range,
				    unsigned offset)
{
	int muxval;
	struct mtk_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);

	muxval = mtk_pmx_find_gpio_mode(pctl, offset);

	if (muxval < 0) {
		dev_err(pctl->dev, "invalid gpio pin %d.\n", offset);
		return -EINVAL;
	}

	mtk_pmx_set_mode(pctldev, offset, muxval);
	mtk_pconf_set_ies_smt(pctl, offset, 1, PIN_CONFIG_INPUT_ENABLE);

	return 0;
}