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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct tegra_soctherm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCROC_THROT_PSKIP_CTRL_CPU_REG (int) ; 
 int /*<<< orphan*/  CCROC_THROT_PSKIP_CTRL_DIVIDEND_MASK ; 
 int /*<<< orphan*/  CCROC_THROT_PSKIP_CTRL_DIVISOR_MASK ; 
 int /*<<< orphan*/  CCROC_THROT_PSKIP_CTRL_ENB_MASK ; 
 int /*<<< orphan*/  CCROC_THROT_PSKIP_RAMP_CPU_REG (int) ; 
 int /*<<< orphan*/  CCROC_THROT_PSKIP_RAMP_DURATION_MASK ; 
 int /*<<< orphan*/  CCROC_THROT_PSKIP_RAMP_STEP_MASK ; 
 int /*<<< orphan*/  REG_SET_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
#define  TEGRA_SOCTHERM_THROT_LEVEL_HIGH 131 
#define  TEGRA_SOCTHERM_THROT_LEVEL_LOW 130 
#define  TEGRA_SOCTHERM_THROT_LEVEL_MED 129 
#define  TEGRA_SOCTHERM_THROT_LEVEL_NONE 128 
 int THROT_DEPTH_DIVIDEND (int) ; 
 int /*<<< orphan*/  ccroc_readl (struct tegra_soctherm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccroc_writel (struct tegra_soctherm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void throttlectl_cpu_level_cfg(struct tegra_soctherm *ts, int level)
{
	u8 depth, dividend;
	u32 r;

	switch (level) {
	case TEGRA_SOCTHERM_THROT_LEVEL_LOW:
		depth = 50;
		break;
	case TEGRA_SOCTHERM_THROT_LEVEL_MED:
		depth = 75;
		break;
	case TEGRA_SOCTHERM_THROT_LEVEL_HIGH:
		depth = 80;
		break;
	case TEGRA_SOCTHERM_THROT_LEVEL_NONE:
		return;
	default:
		return;
	}

	dividend = THROT_DEPTH_DIVIDEND(depth);

	/* setup PSKIP in ccroc nv_therm registers */
	r = ccroc_readl(ts, CCROC_THROT_PSKIP_RAMP_CPU_REG(level));
	r = REG_SET_MASK(r, CCROC_THROT_PSKIP_RAMP_DURATION_MASK, 0xff);
	r = REG_SET_MASK(r, CCROC_THROT_PSKIP_RAMP_STEP_MASK, 0xf);
	ccroc_writel(ts, r, CCROC_THROT_PSKIP_RAMP_CPU_REG(level));

	r = ccroc_readl(ts, CCROC_THROT_PSKIP_CTRL_CPU_REG(level));
	r = REG_SET_MASK(r, CCROC_THROT_PSKIP_CTRL_ENB_MASK, 1);
	r = REG_SET_MASK(r, CCROC_THROT_PSKIP_CTRL_DIVIDEND_MASK, dividend);
	r = REG_SET_MASK(r, CCROC_THROT_PSKIP_CTRL_DIVISOR_MASK, 0xff);
	ccroc_writel(ts, r, CCROC_THROT_PSKIP_CTRL_CPU_REG(level));
}