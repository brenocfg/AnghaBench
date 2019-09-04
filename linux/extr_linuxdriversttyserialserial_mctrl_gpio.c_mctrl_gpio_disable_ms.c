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
struct mctrl_gpios {int mctrl_on; int /*<<< orphan*/ * irq; } ;
typedef  enum mctrl_gpio_idx { ____Placeholder_mctrl_gpio_idx } mctrl_gpio_idx ;

/* Variables and functions */
 int UART_GPIO_MAX ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 

void mctrl_gpio_disable_ms(struct mctrl_gpios *gpios)
{
	enum mctrl_gpio_idx i;

	if (gpios == NULL)
		return;

	if (!gpios->mctrl_on)
		return;

	gpios->mctrl_on = false;

	for (i = 0; i < UART_GPIO_MAX; ++i) {
		if (!gpios->irq[i])
			continue;

		disable_irq(gpios->irq[i]);
	}
}