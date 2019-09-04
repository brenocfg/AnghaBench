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
struct nsp_gpio {int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NSP_GPIO_OUT_EN ; 
 int /*<<< orphan*/  REG ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 struct nsp_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  nsp_set_bit (struct nsp_gpio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int nsp_gpio_direction_input(struct gpio_chip *gc, unsigned gpio)
{
	struct nsp_gpio *chip = gpiochip_get_data(gc);
	unsigned long flags;

	raw_spin_lock_irqsave(&chip->lock, flags);
	nsp_set_bit(chip, REG, NSP_GPIO_OUT_EN, gpio, false);
	raw_spin_unlock_irqrestore(&chip->lock, flags);

	dev_dbg(chip->dev, "gpio:%u set input\n", gpio);
	return 0;
}