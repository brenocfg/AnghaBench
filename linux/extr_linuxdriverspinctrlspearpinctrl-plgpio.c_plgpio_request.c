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
struct TYPE_2__ {int enb; } ;
struct plgpio {unsigned int (* p2o ) (unsigned int) ;int p2o_regs; int /*<<< orphan*/  clk; int /*<<< orphan*/  lock; TYPE_1__ regs; int /*<<< orphan*/  base; } ;
struct gpio_chip {unsigned int ngpio; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int PTO_ENB_REG ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 struct plgpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  pinctrl_gpio_free (int) ; 
 int pinctrl_gpio_request (int) ; 
 int plgpio_direction_input (struct gpio_chip*,unsigned int) ; 
 int /*<<< orphan*/  plgpio_reg_set (int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned int stub1 (unsigned int) ; 

__attribute__((used)) static int plgpio_request(struct gpio_chip *chip, unsigned offset)
{
	struct plgpio *plgpio = gpiochip_get_data(chip);
	int gpio = chip->base + offset;
	unsigned long flags;
	int ret = 0;

	if (offset >= chip->ngpio)
		return -EINVAL;

	ret = pinctrl_gpio_request(gpio);
	if (ret)
		return ret;

	if (!IS_ERR(plgpio->clk)) {
		ret = clk_enable(plgpio->clk);
		if (ret)
			goto err0;
	}

	if (plgpio->regs.enb == -1)
		return 0;

	/*
	 * put gpio in IN mode before enabling it. This make enabling gpio safe
	 */
	ret = plgpio_direction_input(chip, offset);
	if (ret)
		goto err1;

	/* get correct offset for "offset" pin */
	if (plgpio->p2o && (plgpio->p2o_regs & PTO_ENB_REG)) {
		offset = plgpio->p2o(offset);
		if (offset == -1) {
			ret = -EINVAL;
			goto err1;
		}
	}

	spin_lock_irqsave(&plgpio->lock, flags);
	plgpio_reg_set(plgpio->base, offset, plgpio->regs.enb);
	spin_unlock_irqrestore(&plgpio->lock, flags);
	return 0;

err1:
	if (!IS_ERR(plgpio->clk))
		clk_disable(plgpio->clk);
err0:
	pinctrl_gpio_free(gpio);
	return ret;
}