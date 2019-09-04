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
typedef  int u32 ;
struct zynq_pinmux_function {int mux; int mux_mask; int mux_shift; int mux_val; } ;
struct zynq_pinctrl {int pctrl_offset; int /*<<< orphan*/  syscon; struct zynq_pinmux_function* funcs; struct zynq_pctrl_group* groups; } ;
struct zynq_pctrl_group {int* pins; int npins; } ;
struct pinctrl_dev {int dummy; } ;

/* Variables and functions */
 int ZYNQ_PINMUX_MUX_MASK ; 
 int ZYNQ_PINMUX_MUX_SHIFT ; 
 unsigned int ZYNQ_PMUX_sdio0_cd ; 
 unsigned int ZYNQ_PMUX_sdio0_wp ; 
 unsigned int ZYNQ_PMUX_sdio1_cd ; 
 unsigned int ZYNQ_PMUX_sdio1_wp ; 
 struct zynq_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int regmap_read (int /*<<< orphan*/ ,int,int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int zynq_pinmux_set_mux(struct pinctrl_dev *pctldev,
			       unsigned int function,
			       unsigned int  group)
{
	int i, ret;
	struct zynq_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);
	const struct zynq_pctrl_group *pgrp = &pctrl->groups[group];
	const struct zynq_pinmux_function *func = &pctrl->funcs[function];

	/*
	 * SD WP & CD are special. They have dedicated registers
	 * to mux them in
	 */
	if (function == ZYNQ_PMUX_sdio0_cd || function == ZYNQ_PMUX_sdio0_wp ||
			function == ZYNQ_PMUX_sdio1_cd ||
			function == ZYNQ_PMUX_sdio1_wp) {
		u32 reg;

		ret = regmap_read(pctrl->syscon,
				  pctrl->pctrl_offset + func->mux, &reg);
		if (ret)
			return ret;

		reg &= ~func->mux_mask;
		reg |= pgrp->pins[0] << func->mux_shift;
		ret = regmap_write(pctrl->syscon,
				   pctrl->pctrl_offset + func->mux, reg);
		if (ret)
			return ret;
	} else {
		for (i = 0; i < pgrp->npins; i++) {
			unsigned int pin = pgrp->pins[i];
			u32 reg, addr = pctrl->pctrl_offset + (4 * pin);

			ret = regmap_read(pctrl->syscon, addr, &reg);
			if (ret)
				return ret;

			reg &= ~ZYNQ_PINMUX_MUX_MASK;
			reg |= func->mux_val << ZYNQ_PINMUX_MUX_SHIFT;
			ret = regmap_write(pctrl->syscon, addr, reg);
			if (ret)
				return ret;
		}
	}

	return 0;
}