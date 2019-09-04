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
struct TYPE_2__ {scalar_t__ regs; } ;
struct sirfsoc_gpio_chip {TYPE_1__ chip; } ;
struct sirfsoc_gpio_bank {int /*<<< orphan*/  lock; int /*<<< orphan*/  id; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int SIRFSOC_GPIO_CTL_DATAIN_MASK ; 
 scalar_t__ SIRFSOC_GPIO_CTRL (int /*<<< orphan*/ ,unsigned int) ; 
 struct sirfsoc_gpio_chip* gpiochip_get_data (struct gpio_chip*) ; 
 int readl (scalar_t__) ; 
 struct sirfsoc_gpio_bank* sirfsoc_gpio_to_bank (struct sirfsoc_gpio_chip*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int sirfsoc_gpio_get_value(struct gpio_chip *chip, unsigned offset)
{
	struct sirfsoc_gpio_chip *sgpio = gpiochip_get_data(chip);
	struct sirfsoc_gpio_bank *bank = sirfsoc_gpio_to_bank(sgpio, offset);
	u32 val;
	unsigned long flags;

	spin_lock_irqsave(&bank->lock, flags);

	val = readl(sgpio->chip.regs + SIRFSOC_GPIO_CTRL(bank->id, offset));

	spin_unlock_irqrestore(&bank->lock, flags);

	return !!(val & SIRFSOC_GPIO_CTL_DATAIN_MASK);
}