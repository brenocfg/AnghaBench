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
struct pinctrl_dev {int dummy; } ;
struct pic32_pinctrl {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {unsigned int base; } ;
struct pic32_gpio_bank {scalar_t__ reg_base; TYPE_1__ gpio_chip; } ;

/* Variables and functions */
 scalar_t__ ANSEL_REG ; 
 int BIT (unsigned int) ; 
 scalar_t__ CNPD_REG ; 
 scalar_t__ CNPU_REG ; 
 int ENOTSUPP ; 
 scalar_t__ ODCU_REG ; 
#define  PIN_CONFIG_BIAS_PULL_DOWN 134 
#define  PIN_CONFIG_BIAS_PULL_UP 133 
#define  PIN_CONFIG_DRIVE_OPEN_DRAIN 132 
#define  PIN_CONFIG_INPUT_ENABLE 131 
#define  PIN_CONFIG_MICROCHIP_ANALOG 130 
#define  PIN_CONFIG_MICROCHIP_DIGITAL 129 
#define  PIN_CONFIG_OUTPUT 128 
 scalar_t__ TRIS_REG ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 struct pic32_gpio_bank* pctl_to_bank (struct pic32_pinctrl*,unsigned int) ; 
 unsigned long pinconf_to_config_packed (unsigned int,int) ; 
 unsigned int pinconf_to_config_param (unsigned long) ; 
 struct pic32_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static int pic32_pinconf_get(struct pinctrl_dev *pctldev, unsigned pin,
				 unsigned long *config)
{
	struct pic32_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	struct pic32_gpio_bank *bank = pctl_to_bank(pctl, pin);
	unsigned param = pinconf_to_config_param(*config);
	u32 mask = BIT(pin - bank->gpio_chip.base);
	u32 arg;

	switch (param) {
	case PIN_CONFIG_BIAS_PULL_UP:
		arg = !!(readl(bank->reg_base + CNPU_REG) & mask);
		break;
	case PIN_CONFIG_BIAS_PULL_DOWN:
		arg = !!(readl(bank->reg_base + CNPD_REG) & mask);
		break;
	case PIN_CONFIG_MICROCHIP_DIGITAL:
		arg = !(readl(bank->reg_base + ANSEL_REG) & mask);
		break;
	case PIN_CONFIG_MICROCHIP_ANALOG:
		arg = !!(readl(bank->reg_base + ANSEL_REG) & mask);
		break;
	case PIN_CONFIG_DRIVE_OPEN_DRAIN:
		arg = !!(readl(bank->reg_base + ODCU_REG) & mask);
		break;
	case PIN_CONFIG_INPUT_ENABLE:
		arg = !!(readl(bank->reg_base + TRIS_REG) & mask);
		break;
	case PIN_CONFIG_OUTPUT:
		arg = !(readl(bank->reg_base + TRIS_REG) & mask);
		break;
	default:
		dev_err(pctl->dev, "Property %u not supported\n", param);
		return -ENOTSUPP;
	}

	*config = pinconf_to_config_packed(param, arg);

	return 0;
}