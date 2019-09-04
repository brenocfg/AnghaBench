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
struct pinctrl_dev {int dummy; } ;
struct madera_pin_private {int /*<<< orphan*/  dev; struct madera* madera; } ;
struct madera {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  MADERA_GP1_FN_MASK ; 
 int MADERA_GPIO1_CTRL_1 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int,int) ; 
 struct madera_pin_private* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int madera_gpio_request_enable(struct pinctrl_dev *pctldev,
				      struct pinctrl_gpio_range *range,
				      unsigned int offset)
{
	struct madera_pin_private *priv = pinctrl_dev_get_drvdata(pctldev);
	struct madera *madera = priv->madera;
	unsigned int reg = MADERA_GPIO1_CTRL_1 + (2 * offset);
	int ret;

	/* put the pin into GPIO mode */
	ret = regmap_update_bits(madera->regmap, reg, MADERA_GP1_FN_MASK, 1);
	if (ret)
		dev_err(priv->dev, "Failed to write to 0x%x (%d)\n", reg, ret);

	return ret;
}