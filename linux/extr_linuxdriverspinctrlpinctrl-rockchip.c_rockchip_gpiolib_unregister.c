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
struct rockchip_pinctrl {struct rockchip_pin_ctrl* ctrl; } ;
struct rockchip_pin_ctrl {int nr_banks; struct rockchip_pin_bank* pin_banks; } ;
struct rockchip_pin_bank {int /*<<< orphan*/  gpio_chip; int /*<<< orphan*/  valid; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiochip_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rockchip_gpiolib_unregister(struct platform_device *pdev,
						struct rockchip_pinctrl *info)
{
	struct rockchip_pin_ctrl *ctrl = info->ctrl;
	struct rockchip_pin_bank *bank = ctrl->pin_banks;
	int i;

	for (i = 0; i < ctrl->nr_banks; ++i, ++bank) {
		if (!bank->valid)
			continue;
		gpiochip_remove(&bank->gpio_chip);
	}

	return 0;
}