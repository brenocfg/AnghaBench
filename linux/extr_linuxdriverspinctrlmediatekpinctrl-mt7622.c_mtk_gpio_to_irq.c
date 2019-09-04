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
struct mtk_pinctrl {int /*<<< orphan*/  eint; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 struct mtk_pinctrl* gpiochip_get_data (struct gpio_chip*) ; 
 int mtk_eint_find_irq (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int mtk_gpio_to_irq(struct gpio_chip *chip, unsigned int offset)
{
	struct mtk_pinctrl *hw = gpiochip_get_data(chip);
	unsigned long eint_n;

	if (!hw->eint)
		return -ENOTSUPP;

	eint_n = offset;

	return mtk_eint_find_irq(hw->eint, eint_n);
}