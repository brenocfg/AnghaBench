#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u32 ;
struct pinctrl_dev {int dummy; } ;
struct pic32_pinctrl {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {unsigned int base; } ;
struct pic32_gpio_bank {TYPE_1__ gpio_chip; scalar_t__ reg_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANSEL_REG ; 
 unsigned int BIT (unsigned int) ; 
 int /*<<< orphan*/  CNPD_REG ; 
 int /*<<< orphan*/  CNPU_REG ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  ODCU_REG ; 
 scalar_t__ PIC32_CLR (int /*<<< orphan*/ ) ; 
 scalar_t__ PIC32_SET (int /*<<< orphan*/ ) ; 
#define  PIN_CONFIG_BIAS_PULL_DOWN 134 
#define  PIN_CONFIG_BIAS_PULL_UP 133 
#define  PIN_CONFIG_DRIVE_OPEN_DRAIN 132 
#define  PIN_CONFIG_INPUT_ENABLE 131 
#define  PIN_CONFIG_MICROCHIP_ANALOG 130 
#define  PIN_CONFIG_MICROCHIP_DIGITAL 129 
#define  PIN_CONFIG_OUTPUT 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 struct pic32_gpio_bank* pctl_to_bank (struct pic32_pinctrl*,unsigned int) ; 
 int /*<<< orphan*/  pic32_gpio_direction_input (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  pic32_gpio_direction_output (TYPE_1__*,unsigned int,unsigned int) ; 
 unsigned int pinconf_to_config_argument (unsigned long) ; 
 unsigned int pinconf_to_config_param (unsigned long) ; 
 struct pic32_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static int pic32_pinconf_set(struct pinctrl_dev *pctldev, unsigned pin,
				 unsigned long *configs, unsigned num_configs)
{
	struct pic32_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	struct pic32_gpio_bank *bank = pctl_to_bank(pctl, pin);
	unsigned param;
	u32 arg;
	unsigned int i;
	u32 offset = pin - bank->gpio_chip.base;
	u32 mask = BIT(offset);

	dev_dbg(pctl->dev, "setting pin %d bank %d mask 0x%x\n",
		pin, bank->gpio_chip.base, mask);

	for (i = 0; i < num_configs; i++) {
		param = pinconf_to_config_param(configs[i]);
		arg = pinconf_to_config_argument(configs[i]);

		switch (param) {
		case PIN_CONFIG_BIAS_PULL_UP:
			dev_dbg(pctl->dev, "   pullup\n");
			writel(mask, bank->reg_base +PIC32_SET(CNPU_REG));
			break;
		case PIN_CONFIG_BIAS_PULL_DOWN:
			dev_dbg(pctl->dev, "   pulldown\n");
			writel(mask, bank->reg_base + PIC32_SET(CNPD_REG));
			break;
		case PIN_CONFIG_MICROCHIP_DIGITAL:
			dev_dbg(pctl->dev, "   digital\n");
			writel(mask, bank->reg_base + PIC32_CLR(ANSEL_REG));
			break;
		case PIN_CONFIG_MICROCHIP_ANALOG:
			dev_dbg(pctl->dev, "   analog\n");
			writel(mask, bank->reg_base + PIC32_SET(ANSEL_REG));
			break;
		case PIN_CONFIG_DRIVE_OPEN_DRAIN:
			dev_dbg(pctl->dev, "   opendrain\n");
			writel(mask, bank->reg_base + PIC32_SET(ODCU_REG));
			break;
		case PIN_CONFIG_INPUT_ENABLE:
			pic32_gpio_direction_input(&bank->gpio_chip, offset);
			break;
		case PIN_CONFIG_OUTPUT:
			pic32_gpio_direction_output(&bank->gpio_chip,
						    offset, arg);
			break;
		default:
			dev_err(pctl->dev, "Property %u not supported\n",
				param);
			return -ENOTSUPP;
		}
	}

	return 0;
}