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
struct pinctrl_gpio_range {int dummy; } ;
struct pinctrl_dev {int /*<<< orphan*/  dev; } ;
struct ingenic_pinctrl {scalar_t__ version; } ;

/* Variables and functions */
 scalar_t__ ID_JZ4770 ; 
 int /*<<< orphan*/  JZ4740_GPIO_DIR ; 
 int /*<<< orphan*/  JZ4740_GPIO_FUNC ; 
 int /*<<< orphan*/  JZ4740_GPIO_SELECT ; 
 int /*<<< orphan*/  JZ4770_GPIO_INT ; 
 int /*<<< orphan*/  JZ4770_GPIO_MSK ; 
 int /*<<< orphan*/  JZ4770_GPIO_PAT1 ; 
 unsigned int PINS_PER_GPIO_CHIP ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char,unsigned int,char*) ; 
 int /*<<< orphan*/  ingenic_config_pin (struct ingenic_pinctrl*,unsigned int,int /*<<< orphan*/ ,int) ; 
 struct ingenic_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int ingenic_pinmux_gpio_set_direction(struct pinctrl_dev *pctldev,
		struct pinctrl_gpio_range *range,
		unsigned int pin, bool input)
{
	struct ingenic_pinctrl *jzpc = pinctrl_dev_get_drvdata(pctldev);
	unsigned int idx = pin % PINS_PER_GPIO_CHIP;
	unsigned int offt = pin / PINS_PER_GPIO_CHIP;

	dev_dbg(pctldev->dev, "set pin P%c%u to %sput\n",
			'A' + offt, idx, input ? "in" : "out");

	if (jzpc->version >= ID_JZ4770) {
		ingenic_config_pin(jzpc, pin, JZ4770_GPIO_INT, false);
		ingenic_config_pin(jzpc, pin, JZ4770_GPIO_MSK, true);
		ingenic_config_pin(jzpc, pin, JZ4770_GPIO_PAT1, input);
	} else {
		ingenic_config_pin(jzpc, pin, JZ4740_GPIO_SELECT, false);
		ingenic_config_pin(jzpc, pin, JZ4740_GPIO_DIR, !input);
		ingenic_config_pin(jzpc, pin, JZ4740_GPIO_FUNC, false);
	}

	return 0;
}