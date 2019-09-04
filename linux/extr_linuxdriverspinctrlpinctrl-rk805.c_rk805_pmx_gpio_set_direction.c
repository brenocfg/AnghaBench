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
struct rk805_pctrl_info {int /*<<< orphan*/  dev; TYPE_2__* pin_cfg; TYPE_1__* rk808; } ;
struct pinctrl_gpio_range {int dummy; } ;
struct pinctrl_dev {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dir_msk; int /*<<< orphan*/  reg; } ;
struct TYPE_3__ {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  RK805_PINMUX_GPIO ; 
 int _rk805_pinctrl_set_mux (struct pinctrl_dev*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 struct rk805_pctrl_info* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rk805_pmx_gpio_set_direction(struct pinctrl_dev *pctldev,
					struct pinctrl_gpio_range *range,
					unsigned int offset, bool input)
{
	struct rk805_pctrl_info *pci = pinctrl_dev_get_drvdata(pctldev);
	int ret;

	/* switch to gpio function */
	ret = _rk805_pinctrl_set_mux(pctldev, offset, RK805_PINMUX_GPIO);
	if (ret) {
		dev_err(pci->dev, "set gpio%d mux failed\n", offset);
		return ret;
	}

	/* set direction */
	if (!pci->pin_cfg[offset].dir_msk)
		return 0;

	ret = regmap_update_bits(pci->rk808->regmap,
				 pci->pin_cfg[offset].reg,
				 pci->pin_cfg[offset].dir_msk,
				 input ? 0 : pci->pin_cfg[offset].dir_msk);
	if (ret) {
		dev_err(pci->dev, "set gpio%d direction failed\n", offset);
		return ret;
	}

	return ret;
}