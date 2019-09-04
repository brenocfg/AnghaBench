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
struct mtk_pinctrl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTK_GPIO_MODE ; 
 int /*<<< orphan*/  PINCTRL_PIN_REG_MODE ; 
 int mtk_hw_set_value (struct mtk_pinctrl*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mtk_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int mtk_pinmux_gpio_request_enable(struct pinctrl_dev *pctldev,
					  struct pinctrl_gpio_range *range,
					  unsigned int pin)
{
	struct mtk_pinctrl *hw = pinctrl_dev_get_drvdata(pctldev);

	return mtk_hw_set_value(hw, pin, PINCTRL_PIN_REG_MODE, MTK_GPIO_MODE);
}