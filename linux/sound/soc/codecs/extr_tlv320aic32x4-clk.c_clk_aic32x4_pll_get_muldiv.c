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
struct clk_aic32x4_pll_muldiv {unsigned int r; unsigned int p; unsigned int j; unsigned int d; } ;
struct clk_aic32x4 {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  AIC32X4_PLLDLSB ; 
 int /*<<< orphan*/  AIC32X4_PLLDMSB ; 
 int /*<<< orphan*/  AIC32X4_PLLJ ; 
 int /*<<< orphan*/  AIC32X4_PLLPR ; 
 unsigned int AIC32X4_PLL_P_MASK ; 
 unsigned int AIC32X4_PLL_P_SHIFT ; 
 unsigned int AIC32X4_PLL_R_MASK ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int clk_aic32x4_pll_get_muldiv(struct clk_aic32x4 *pll,
			struct clk_aic32x4_pll_muldiv *settings)
{
	/*	Change to use regmap_bulk_read? */
	unsigned int val;
	int ret;

	ret = regmap_read(pll->regmap, AIC32X4_PLLPR, &val);
	if (ret < 0)
		return ret;
	settings->r = val & AIC32X4_PLL_R_MASK;
	settings->p = (val & AIC32X4_PLL_P_MASK) >> AIC32X4_PLL_P_SHIFT;

	ret = regmap_read(pll->regmap, AIC32X4_PLLJ, &val);
	if (ret < 0)
		return ret;
	settings->j = val;

	ret = regmap_read(pll->regmap, AIC32X4_PLLDMSB, &val);
	if (ret < 0)
		return ret;
	settings->d = val << 8;

	ret = regmap_read(pll->regmap, AIC32X4_PLLDLSB,	 &val);
	if (ret < 0)
		return ret;
	settings->d |= val;

	return 0;
}