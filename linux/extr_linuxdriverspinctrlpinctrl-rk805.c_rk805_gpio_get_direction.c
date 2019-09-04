#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rk805_pctrl_info {TYPE_2__* pin_cfg; int /*<<< orphan*/  dev; TYPE_1__* rk808; } ;
struct gpio_chip {int dummy; } ;
struct TYPE_4__ {unsigned int dir_msk; int /*<<< orphan*/  reg; } ;
struct TYPE_3__ {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 struct rk805_pctrl_info* gpiochip_get_data (struct gpio_chip*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int rk805_gpio_get_direction(struct gpio_chip *chip, unsigned int offset)
{
	struct rk805_pctrl_info *pci = gpiochip_get_data(chip);
	unsigned int val;
	int ret;

	/* default output*/
	if (!pci->pin_cfg[offset].dir_msk)
		return 0;

	ret = regmap_read(pci->rk808->regmap,
			  pci->pin_cfg[offset].reg,
			  &val);
	if (ret) {
		dev_err(pci->dev, "get gpio%d direction failed\n", offset);
		return ret;
	}

	return !(val & pci->pin_cfg[offset].dir_msk);
}