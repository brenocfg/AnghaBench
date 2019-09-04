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
struct tegra_xusb {int /*<<< orphan*/  dev; struct clk* clk_m; struct clk* pll_u_480m; struct clk* ss_src_clk; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  TEGRA_XHCI_SS_HIGH_SPEED 129 
#define  TEGRA_XHCI_SS_LOW_SPEED 128 
 struct clk* clk_get_parent (struct clk*) ; 
 unsigned long clk_get_rate (struct clk*) ; 
 int clk_set_parent (struct clk*,struct clk*) ; 
 int clk_set_rate (struct clk*,unsigned long) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int tegra_xusb_set_ss_clk(struct tegra_xusb *tegra,
				 unsigned long rate)
{
	unsigned long new_parent_rate, old_parent_rate;
	struct clk *clk = tegra->ss_src_clk;
	unsigned int div;
	int err;

	if (clk_get_rate(clk) == rate)
		return 0;

	switch (rate) {
	case TEGRA_XHCI_SS_HIGH_SPEED:
		/*
		 * Reparent to PLLU_480M. Set divider first to avoid
		 * overclocking.
		 */
		old_parent_rate = clk_get_rate(clk_get_parent(clk));
		new_parent_rate = clk_get_rate(tegra->pll_u_480m);
		div = new_parent_rate / rate;

		err = clk_set_rate(clk, old_parent_rate / div);
		if (err)
			return err;

		err = clk_set_parent(clk, tegra->pll_u_480m);
		if (err)
			return err;

		/*
		 * The rate should already be correct, but set it again just
		 * to be sure.
		 */
		err = clk_set_rate(clk, rate);
		if (err)
			return err;

		break;

	case TEGRA_XHCI_SS_LOW_SPEED:
		/* Reparent to CLK_M */
		err = clk_set_parent(clk, tegra->clk_m);
		if (err)
			return err;

		err = clk_set_rate(clk, rate);
		if (err)
			return err;

		break;

	default:
		dev_err(tegra->dev, "Invalid SS rate: %lu Hz\n", rate);
		return -EINVAL;
	}

	if (clk_get_rate(clk) != rate) {
		dev_err(tegra->dev, "SS clock doesn't match requested rate\n");
		return -EINVAL;
	}

	return 0;
}