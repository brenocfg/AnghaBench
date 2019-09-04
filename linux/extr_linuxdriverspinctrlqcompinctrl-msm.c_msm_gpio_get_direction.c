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
struct msm_pingroup {int /*<<< orphan*/  oe_bit; scalar_t__ ctl_reg; } ;
struct msm_pinctrl {scalar_t__ regs; TYPE_1__* soc; } ;
struct gpio_chip {int dummy; } ;
struct TYPE_2__ {struct msm_pingroup* groups; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 struct msm_pinctrl* gpiochip_get_data (struct gpio_chip*) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static int msm_gpio_get_direction(struct gpio_chip *chip, unsigned int offset)
{
	struct msm_pinctrl *pctrl = gpiochip_get_data(chip);
	const struct msm_pingroup *g;
	u32 val;

	g = &pctrl->soc->groups[offset];

	val = readl(pctrl->regs + g->ctl_reg);

	/* 0 = output, 1 = input */
	return val & BIT(g->oe_bit) ? 0 : 1;
}