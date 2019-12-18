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
typedef  int u64 ;
typedef  int u32 ;
struct clk_aic32x4_pll_muldiv {unsigned long p; int r; int j; int d; } ;

/* Variables and functions */
 unsigned long AIC32X4_MAX_PLL_CLKIN ; 
 int /*<<< orphan*/  do_div (int,unsigned long) ; 

__attribute__((used)) static int clk_aic32x4_pll_calc_muldiv(struct clk_aic32x4_pll_muldiv *settings,
			unsigned long rate, unsigned long parent_rate)
{
	u64 multiplier;

	settings->p = parent_rate / AIC32X4_MAX_PLL_CLKIN + 1;
	if (settings->p > 8)
		return -1;

	/*
	 * We scale this figure by 10000 so that we can get the decimal part
	 * of the multiplier.	This is because we can't do floating point
	 * math in the kernel.
	 */
	multiplier = (u64) rate * settings->p * 10000;
	do_div(multiplier, parent_rate);

	/*
	 * J can't be over 64, so R can scale this.
	 * R can't be greater than 4.
	 */
	settings->r = ((u32) multiplier / 640000) + 1;
	if (settings->r > 4)
		return -1;
	do_div(multiplier, settings->r);

	/*
	 * J can't be < 1.
	 */
	if (multiplier < 10000)
		return -1;

	/* Figure out the integer part, J, and the fractional part, D. */
	settings->j = (u32) multiplier / 10000;
	settings->d = (u32) multiplier % 10000;

	return 0;
}