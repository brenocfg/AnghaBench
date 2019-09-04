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
struct mtk_pinctrl {TYPE_1__* devdata; } ;
struct gpio_chip {int dummy; } ;
struct TYPE_2__ {unsigned int dout_offset; } ;

/* Variables and functions */
 unsigned int BIT (unsigned int) ; 
 unsigned int CLR_ADDR (unsigned int,struct mtk_pinctrl*) ; 
 unsigned int SET_ADDR (unsigned int,struct mtk_pinctrl*) ; 
 struct mtk_pinctrl* gpiochip_get_data (struct gpio_chip*) ; 
 unsigned int mtk_get_port (struct mtk_pinctrl*,unsigned int) ; 
 int /*<<< orphan*/  mtk_get_regmap (struct mtk_pinctrl*,unsigned int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static void mtk_gpio_set(struct gpio_chip *chip, unsigned offset, int value)
{
	unsigned int reg_addr;
	unsigned int bit;
	struct mtk_pinctrl *pctl = gpiochip_get_data(chip);

	reg_addr = mtk_get_port(pctl, offset) + pctl->devdata->dout_offset;
	bit = BIT(offset & 0xf);

	if (value)
		reg_addr = SET_ADDR(reg_addr, pctl);
	else
		reg_addr = CLR_ADDR(reg_addr, pctl);

	regmap_write(mtk_get_regmap(pctl, offset), reg_addr, bit);
}