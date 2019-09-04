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
struct tegra_soctherm {scalar_t__ regs; scalar_t__ clk_regs; TYPE_1__* soc; } ;
struct device {int dummy; } ;
struct TYPE_2__ {scalar_t__ use_ccroc; } ;

/* Variables and functions */
 scalar_t__ CAR_SUPER_CCLKG_DIVIDER ; 
 int /*<<< orphan*/  CCROC_GLOBAL_CFG ; 
 int /*<<< orphan*/  CCROC_SUPER_CCLKG_DIVIDER ; 
 int /*<<< orphan*/  CDIVG_USE_THERM_CONTROLS_MASK ; 
 int REG_SET_MASK (int,int /*<<< orphan*/ ,int) ; 
 int STATS_CTL_CLR_DN ; 
 int STATS_CTL_CLR_UP ; 
 int STATS_CTL_EN_DN ; 
 int STATS_CTL_EN_UP ; 
 int /*<<< orphan*/  TEGRA_SOCTHERM_THROT_LEVEL_HIGH ; 
 int /*<<< orphan*/  TEGRA_SOCTHERM_THROT_LEVEL_LOW ; 
 int /*<<< orphan*/  TEGRA_SOCTHERM_THROT_LEVEL_MED ; 
 scalar_t__ THERMCTL_STATS_CTL ; 
 int THROTTLE_SIZE ; 
 scalar_t__ THROT_GLOBAL_CFG ; 
 int /*<<< orphan*/  THROT_GLOBAL_ENB_MASK ; 
 int ccroc_readl (struct tegra_soctherm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccroc_writel (struct tegra_soctherm*,int,int /*<<< orphan*/ ) ; 
 struct tegra_soctherm* dev_get_drvdata (struct device*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  soctherm_throttle_program (struct tegra_soctherm*,int) ; 
 int /*<<< orphan*/  throttlectl_cpu_level_cfg (struct tegra_soctherm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void tegra_soctherm_throttle(struct device *dev)
{
	struct tegra_soctherm *ts = dev_get_drvdata(dev);
	u32 v;
	int i;

	/* configure LOW, MED and HIGH levels for CCROC NV_THERM */
	if (ts->soc->use_ccroc) {
		throttlectl_cpu_level_cfg(ts, TEGRA_SOCTHERM_THROT_LEVEL_LOW);
		throttlectl_cpu_level_cfg(ts, TEGRA_SOCTHERM_THROT_LEVEL_MED);
		throttlectl_cpu_level_cfg(ts, TEGRA_SOCTHERM_THROT_LEVEL_HIGH);
	}

	/* Thermal HW throttle programming */
	for (i = 0; i < THROTTLE_SIZE; i++)
		soctherm_throttle_program(ts, i);

	v = REG_SET_MASK(0, THROT_GLOBAL_ENB_MASK, 1);
	if (ts->soc->use_ccroc) {
		ccroc_writel(ts, v, CCROC_GLOBAL_CFG);

		v = ccroc_readl(ts, CCROC_SUPER_CCLKG_DIVIDER);
		v = REG_SET_MASK(v, CDIVG_USE_THERM_CONTROLS_MASK, 1);
		ccroc_writel(ts, v, CCROC_SUPER_CCLKG_DIVIDER);
	} else {
		writel(v, ts->regs + THROT_GLOBAL_CFG);

		v = readl(ts->clk_regs + CAR_SUPER_CCLKG_DIVIDER);
		v = REG_SET_MASK(v, CDIVG_USE_THERM_CONTROLS_MASK, 1);
		writel(v, ts->clk_regs + CAR_SUPER_CCLKG_DIVIDER);
	}

	/* initialize stats collection */
	v = STATS_CTL_CLR_DN | STATS_CTL_EN_DN |
	    STATS_CTL_CLR_UP | STATS_CTL_EN_UP;
	writel(v, ts->regs + THERMCTL_STATS_CTL);
}