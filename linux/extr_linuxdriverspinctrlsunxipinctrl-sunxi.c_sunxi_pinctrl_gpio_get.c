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
typedef  int u8 ;
typedef  int u32 ;
struct sunxi_pinctrl {int membase; int /*<<< orphan*/  pctl_dev; TYPE_1__* desc; } ;
struct gpio_chip {unsigned int base; } ;
struct TYPE_2__ {scalar_t__ irq_read_needs_mux; } ;

/* Variables and functions */
 int DATA_PINS_MASK ; 
 int /*<<< orphan*/  SUN4I_FUNC_INPUT ; 
 int /*<<< orphan*/  SUN4I_FUNC_IRQ ; 
 struct sunxi_pinctrl* gpiochip_get_data (struct gpio_chip*) ; 
 scalar_t__ gpiochip_line_is_irq (struct gpio_chip*,unsigned int) ; 
 int readl (int) ; 
 int sunxi_data_offset (unsigned int) ; 
 int sunxi_data_reg (unsigned int) ; 
 int /*<<< orphan*/  sunxi_pmx_set (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sunxi_pinctrl_gpio_get(struct gpio_chip *chip, unsigned offset)
{
	struct sunxi_pinctrl *pctl = gpiochip_get_data(chip);
	u32 reg = sunxi_data_reg(offset);
	u8 index = sunxi_data_offset(offset);
	bool set_mux = pctl->desc->irq_read_needs_mux &&
		gpiochip_line_is_irq(chip, offset);
	u32 pin = offset + chip->base;
	u32 val;

	if (set_mux)
		sunxi_pmx_set(pctl->pctl_dev, pin, SUN4I_FUNC_INPUT);

	val = (readl(pctl->membase + reg) >> index) & DATA_PINS_MASK;

	if (set_mux)
		sunxi_pmx_set(pctl->pctl_dev, pin, SUN4I_FUNC_IRQ);

	return !!val;
}