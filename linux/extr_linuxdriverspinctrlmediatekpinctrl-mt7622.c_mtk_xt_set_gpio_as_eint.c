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
struct mtk_pinctrl {int dummy; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTK_ENABLE ; 
 int /*<<< orphan*/  MTK_GPIO_MODE ; 
 int /*<<< orphan*/  MTK_INPUT ; 
 int /*<<< orphan*/  PINCTRL_PIN_REG_DIR ; 
 int /*<<< orphan*/  PINCTRL_PIN_REG_MODE ; 
 int /*<<< orphan*/  PINCTRL_PIN_REG_SMT ; 
 int mtk_hw_set_value (struct mtk_pinctrl*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mtk_xt_get_gpio_n (struct mtk_pinctrl*,unsigned long,unsigned int*,struct gpio_chip**) ; 

__attribute__((used)) static int mtk_xt_set_gpio_as_eint(void *data, unsigned long eint_n)
{
	struct mtk_pinctrl *hw = (struct mtk_pinctrl *)data;
	struct gpio_chip *gpio_chip;
	unsigned int gpio_n;
	int err;

	err = mtk_xt_get_gpio_n(hw, eint_n, &gpio_n, &gpio_chip);
	if (err)
		return err;

	err = mtk_hw_set_value(hw, gpio_n, PINCTRL_PIN_REG_MODE,
			       MTK_GPIO_MODE);
	if (err)
		return err;

	err = mtk_hw_set_value(hw, gpio_n, PINCTRL_PIN_REG_DIR, MTK_INPUT);
	if (err)
		return err;

	err = mtk_hw_set_value(hw, gpio_n, PINCTRL_PIN_REG_SMT, MTK_ENABLE);
	if (err)
		return err;

	return 0;
}