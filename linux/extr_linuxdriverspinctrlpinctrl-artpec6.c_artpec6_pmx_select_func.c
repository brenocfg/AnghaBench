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
struct pinctrl_dev {int dummy; } ;
struct artpec6_pmx {scalar_t__ base; } ;
struct TYPE_2__ {int num_pins; scalar_t__* pins; unsigned int config; } ;

/* Variables and functions */
 unsigned int ARTPEC6_CONFIG_0 ; 
 scalar_t__ ARTPEC6_MAX_MUXABLE ; 
 unsigned int ARTPEC6_PINMUX_SEL_MASK ; 
 unsigned int ARTPEC6_PINMUX_SEL_SHIFT ; 
 TYPE_1__* artpec6_pin_groups ; 
 int /*<<< orphan*/  artpec6_pmx_get_fname (struct pinctrl_dev*,unsigned int) ; 
 unsigned int artpec6_pmx_reg_offset (scalar_t__) ; 
 struct artpec6_pmx* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void artpec6_pmx_select_func(struct pinctrl_dev *pctldev,
				    unsigned int function, unsigned int group,
				    bool enable)
{
	unsigned int regval, val;
	unsigned int reg;
	int i;
	struct artpec6_pmx *pmx = pinctrl_dev_get_drvdata(pctldev);

	for (i = 0; i < artpec6_pin_groups[group].num_pins; i++) {
		/*
		 * Registers for pins above a ARTPEC6_MAX_MUXABLE
		 * do not have a SEL field and are always selected.
		 */
		if (artpec6_pin_groups[group].pins[i] > ARTPEC6_MAX_MUXABLE)
			continue;

		if (!strcmp(artpec6_pmx_get_fname(pctldev, function), "gpio")) {
			/* GPIO is always config 0 */
			val = ARTPEC6_CONFIG_0 << ARTPEC6_PINMUX_SEL_SHIFT;
		} else {
			if (enable)
				val = artpec6_pin_groups[group].config
					<< ARTPEC6_PINMUX_SEL_SHIFT;
			else
				val = ARTPEC6_CONFIG_0
					<< ARTPEC6_PINMUX_SEL_SHIFT;
		}

		reg = artpec6_pmx_reg_offset(artpec6_pin_groups[group].pins[i]);

		regval = readl(pmx->base + reg);
		regval &= ~ARTPEC6_PINMUX_SEL_MASK;
		regval |= val;
		writel(regval, pmx->base + reg);
	}
}