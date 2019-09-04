#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pmic_gpio_state {TYPE_3__* ctrl; } ;
struct pmic_gpio_pad {int out_value; scalar_t__ input_enabled; int /*<<< orphan*/  is_enabled; } ;
struct gpio_chip {int dummy; } ;
struct TYPE_6__ {TYPE_2__* desc; } ;
struct TYPE_5__ {TYPE_1__* pins; } ;
struct TYPE_4__ {struct pmic_gpio_pad* drv_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PMIC_MPP_REG_RT_STS ; 
 int PMIC_MPP_REG_RT_STS_VAL_MASK ; 
 struct pmic_gpio_state* gpiochip_get_data (struct gpio_chip*) ; 
 int pmic_gpio_read (struct pmic_gpio_state*,struct pmic_gpio_pad*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pmic_gpio_get(struct gpio_chip *chip, unsigned pin)
{
	struct pmic_gpio_state *state = gpiochip_get_data(chip);
	struct pmic_gpio_pad *pad;
	int ret;

	pad = state->ctrl->desc->pins[pin].drv_data;

	if (!pad->is_enabled)
		return -EINVAL;

	if (pad->input_enabled) {
		ret = pmic_gpio_read(state, pad, PMIC_MPP_REG_RT_STS);
		if (ret < 0)
			return ret;

		pad->out_value = ret & PMIC_MPP_REG_RT_STS_VAL_MASK;
	}

	return !!pad->out_value;
}