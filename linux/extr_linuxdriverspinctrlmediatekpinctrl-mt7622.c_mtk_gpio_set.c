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
 int /*<<< orphan*/  PINCTRL_PIN_REG_DO ; 
 struct mtk_pinctrl* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  mtk_hw_set_value (struct mtk_pinctrl*,unsigned int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mtk_gpio_set(struct gpio_chip *chip, unsigned int gpio, int value)
{
	struct mtk_pinctrl *hw = gpiochip_get_data(chip);

	mtk_hw_set_value(hw, gpio, PINCTRL_PIN_REG_DO, !!value);
}