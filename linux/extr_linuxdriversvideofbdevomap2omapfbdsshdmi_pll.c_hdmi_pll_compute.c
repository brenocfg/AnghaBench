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
typedef  unsigned long u64 ;
typedef  unsigned int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  clkin; struct dss_pll_hw* hw; } ;
struct hdmi_pll_data {TYPE_1__ pll; } ;
struct dss_pll_hw {int fint_max; int /*<<< orphan*/  clkdco_min; } ;
struct dss_pll_clock_info {unsigned int n; unsigned int m; unsigned int mf; unsigned int* mX; unsigned int sd; unsigned long fint; unsigned long clkdco; unsigned long* clkout; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (unsigned long,int) ; 
 int /*<<< orphan*/  DSSDBG (char*,unsigned long,unsigned long,...) ; 
 scalar_t__ WARN_ON (int) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 scalar_t__ div_u64 (unsigned long,int) ; 
 unsigned long roundup (int /*<<< orphan*/ ,unsigned long) ; 

void hdmi_pll_compute(struct hdmi_pll_data *pll,
	unsigned long target_tmds, struct dss_pll_clock_info *pi)
{
	unsigned long fint, clkdco, clkout;
	unsigned long target_bitclk, target_clkdco;
	unsigned long min_dco;
	unsigned n, m, mf, m2, sd;
	unsigned long clkin;
	const struct dss_pll_hw *hw = pll->pll.hw;

	clkin = clk_get_rate(pll->pll.clkin);

	DSSDBG("clkin %lu, target tmds %lu\n", clkin, target_tmds);

	target_bitclk = target_tmds * 10;

	/* Fint */
	n = DIV_ROUND_UP(clkin, hw->fint_max);
	fint = clkin / n;

	/* adjust m2 so that the clkdco will be high enough */
	min_dco = roundup(hw->clkdco_min, fint);
	m2 = DIV_ROUND_UP(min_dco, target_bitclk);
	if (m2 == 0)
		m2 = 1;

	target_clkdco = target_bitclk * m2;
	m = target_clkdco / fint;

	clkdco = fint * m;

	/* adjust clkdco with fractional mf */
	if (WARN_ON(target_clkdco - clkdco > fint))
		mf = 0;
	else
		mf = (u32)div_u64(262144ull * (target_clkdco - clkdco), fint);

	if (mf > 0)
		clkdco += (u32)div_u64((u64)mf * fint, 262144);

	clkout = clkdco / m2;

	/* sigma-delta */
	sd = DIV_ROUND_UP(fint * m, 250000000);

	DSSDBG("N = %u, M = %u, M.f = %u, M2 = %u, SD = %u\n",
		n, m, mf, m2, sd);
	DSSDBG("Fint %lu, clkdco %lu, clkout %lu\n", fint, clkdco, clkout);

	pi->n = n;
	pi->m = m;
	pi->mf = mf;
	pi->mX[0] = m2;
	pi->sd = sd;

	pi->fint = fint;
	pi->clkdco = clkdco;
	pi->clkout[0] = clkout;
}