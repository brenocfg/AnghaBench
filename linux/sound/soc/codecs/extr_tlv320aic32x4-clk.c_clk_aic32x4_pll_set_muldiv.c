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
struct clk_aic32x4_pll_muldiv {int r; int p; int j; int d; } ;
struct clk_aic32x4 {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  AIC32X4_PLLDLSB ; 
 int /*<<< orphan*/  AIC32X4_PLLDMSB ; 
 int /*<<< orphan*/  AIC32X4_PLLJ ; 
 int /*<<< orphan*/  AIC32X4_PLLPR ; 
 int /*<<< orphan*/  AIC32X4_PLL_P_MASK ; 
 int AIC32X4_PLL_P_SHIFT ; 
 int /*<<< orphan*/  AIC32X4_PLL_R_MASK ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int clk_aic32x4_pll_set_muldiv(struct clk_aic32x4 *pll,
			struct clk_aic32x4_pll_muldiv *settings)
{
	int ret;
	/*	Change to use regmap_bulk_write for some if not all? */

	ret = regmap_update_bits(pll->regmap, AIC32X4_PLLPR,
				AIC32X4_PLL_R_MASK, settings->r);
	if (ret < 0)
		return ret;

	ret = regmap_update_bits(pll->regmap, AIC32X4_PLLPR,
				AIC32X4_PLL_P_MASK,
				settings->p << AIC32X4_PLL_P_SHIFT);
	if (ret < 0)
		return ret;

	ret = regmap_write(pll->regmap, AIC32X4_PLLJ, settings->j);
	if (ret < 0)
		return ret;

	ret = regmap_write(pll->regmap, AIC32X4_PLLDMSB, (settings->d >> 8));
	if (ret < 0)
		return ret;
	ret = regmap_write(pll->regmap, AIC32X4_PLLDLSB, (settings->d & 0xff));
	if (ret < 0)
		return ret;

	return 0;
}