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
typedef  int u32 ;
struct rockchip_pin_bank {int /*<<< orphan*/  clk; scalar_t__ reg_base; int /*<<< orphan*/  name; TYPE_1__* drvdata; } ;
struct gpio_chip {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 scalar_t__ GPIO_SWPORT_DDR ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct rockchip_pin_bank* gpiochip_get_data (struct gpio_chip*) ; 
 int readl_relaxed (scalar_t__) ; 

__attribute__((used)) static int rockchip_gpio_get_direction(struct gpio_chip *chip, unsigned offset)
{
	struct rockchip_pin_bank *bank = gpiochip_get_data(chip);
	u32 data;
	int ret;

	ret = clk_enable(bank->clk);
	if (ret < 0) {
		dev_err(bank->drvdata->dev,
			"failed to enable clock for bank %s\n", bank->name);
		return ret;
	}
	data = readl_relaxed(bank->reg_base + GPIO_SWPORT_DDR);
	clk_disable(bank->clk);

	return !(data & BIT(offset));
}