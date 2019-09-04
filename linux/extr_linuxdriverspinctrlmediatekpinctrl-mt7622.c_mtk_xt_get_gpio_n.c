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
struct gpio_chip {int dummy; } ;
struct mtk_pinctrl {struct gpio_chip chip; } ;

/* Variables and functions */

__attribute__((used)) static int mtk_xt_get_gpio_n(void *data, unsigned long eint_n,
			     unsigned int *gpio_n,
			     struct gpio_chip **gpio_chip)
{
	struct mtk_pinctrl *hw = (struct mtk_pinctrl *)data;

	*gpio_chip = &hw->chip;
	*gpio_n = eint_n;

	return 0;
}