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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ regs; } ;
struct sirfsoc_gpio_chip {TYPE_1__ chip; } ;
struct sirfsoc_gpio_bank {int /*<<< orphan*/  lock; int /*<<< orphan*/  id; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIRFSOC_GPIO_CTL_DATAOUT_MASK ; 
 scalar_t__ SIRFSOC_GPIO_CTRL (int /*<<< orphan*/ ,unsigned int) ; 
 struct sirfsoc_gpio_chip* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 struct sirfsoc_gpio_bank* sirfsoc_gpio_to_bank (struct sirfsoc_gpio_chip*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void sirfsoc_gpio_set_value(struct gpio_chip *chip, unsigned offset,
	int value)
{
	struct sirfsoc_gpio_chip *sgpio = gpiochip_get_data(chip);
	struct sirfsoc_gpio_bank *bank = sirfsoc_gpio_to_bank(sgpio, offset);
	u32 ctrl;
	unsigned long flags;

	spin_lock_irqsave(&bank->lock, flags);

	ctrl = readl(sgpio->chip.regs + SIRFSOC_GPIO_CTRL(bank->id, offset));
	if (value)
		ctrl |= SIRFSOC_GPIO_CTL_DATAOUT_MASK;
	else
		ctrl &= ~SIRFSOC_GPIO_CTL_DATAOUT_MASK;
	writel(ctrl, sgpio->chip.regs + SIRFSOC_GPIO_CTRL(bank->id, offset));

	spin_unlock_irqrestore(&bank->lock, flags);
}