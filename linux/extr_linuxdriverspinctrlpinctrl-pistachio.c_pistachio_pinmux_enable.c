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
typedef  unsigned int u32 ;
struct pistachio_pinctrl {int /*<<< orphan*/  pctldev; int /*<<< orphan*/  dev; struct pistachio_function* functions; struct pistachio_pin_group* groups; } ;
struct pistachio_pin_group {scalar_t__ mux_reg; unsigned int* mux_option; unsigned int mux_mask; unsigned int mux_shift; scalar_t__ pin; } ;
struct pistachio_function {unsigned int* scenarios; unsigned int nscenarios; scalar_t__ scenario_reg; unsigned int scenario_mask; unsigned int scenario_shift; } ;
struct pinctrl_gpio_range {scalar_t__ pin_base; int /*<<< orphan*/  gc; } ;
struct pinctrl_dev {int dummy; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (unsigned int*) ; 
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  gpio_disable (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  gpiochip_get_data (int /*<<< orphan*/ ) ; 
 unsigned int pctl_readl (struct pistachio_pinctrl*,scalar_t__) ; 
 int /*<<< orphan*/  pctl_writel (struct pistachio_pinctrl*,unsigned int,scalar_t__) ; 
 struct pistachio_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 struct pinctrl_gpio_range* pinctrl_find_gpio_range_from_pin (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int pistachio_pinmux_enable(struct pinctrl_dev *pctldev,
				   unsigned func, unsigned group)
{
	struct pistachio_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	const struct pistachio_pin_group *pg = &pctl->groups[group];
	const struct pistachio_function *pf = &pctl->functions[func];
	struct pinctrl_gpio_range *range;
	unsigned int i;
	u32 val;

	if (pg->mux_reg > 0) {
		for (i = 0; i < ARRAY_SIZE(pg->mux_option); i++) {
			if (pg->mux_option[i] == func)
				break;
		}
		if (i == ARRAY_SIZE(pg->mux_option)) {
			dev_err(pctl->dev, "Cannot mux pin %u to function %u\n",
				group, func);
			return -EINVAL;
		}

		val = pctl_readl(pctl, pg->mux_reg);
		val &= ~(pg->mux_mask << pg->mux_shift);
		val |= i << pg->mux_shift;
		pctl_writel(pctl, val, pg->mux_reg);

		if (pf->scenarios) {
			for (i = 0; i < pf->nscenarios; i++) {
				if (pf->scenarios[i] == group)
					break;
			}
			if (WARN_ON(i == pf->nscenarios))
				return -EINVAL;

			val = pctl_readl(pctl, pf->scenario_reg);
			val &= ~(pf->scenario_mask << pf->scenario_shift);
			val |= i << pf->scenario_shift;
			pctl_writel(pctl, val, pf->scenario_reg);
		}
	}

	range = pinctrl_find_gpio_range_from_pin(pctl->pctldev, pg->pin);
	if (range)
		gpio_disable(gpiochip_get_data(range->gc), pg->pin - range->pin_base);

	return 0;
}