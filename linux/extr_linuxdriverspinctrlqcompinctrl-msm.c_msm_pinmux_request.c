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
struct pinctrl_dev {int dummy; } ;
struct gpio_chip {int dummy; } ;
struct msm_pinctrl {struct gpio_chip chip; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ gpiochip_line_is_valid (struct gpio_chip*,unsigned int) ; 
 struct msm_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int msm_pinmux_request(struct pinctrl_dev *pctldev, unsigned offset)
{
	struct msm_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);
	struct gpio_chip *chip = &pctrl->chip;

	return gpiochip_line_is_valid(chip, offset) ? 0 : -EINVAL;
}