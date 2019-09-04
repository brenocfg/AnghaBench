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
typedef  scalar_t__ u32 ;
struct stm32_usbphyc {int /*<<< orphan*/  dev; scalar_t__ base; int /*<<< orphan*/  clk; } ;
struct pll_params {scalar_t__ frac; scalar_t__ ndiv; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FIELD_GET (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ FIELD_PREP (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ PLLDITHEN0 ; 
 scalar_t__ PLLDITHEN1 ; 
 scalar_t__ PLLFRACCTL ; 
 int /*<<< orphan*/  PLLFRACIN ; 
 int /*<<< orphan*/  PLLNDIV ; 
 scalar_t__ PLLSTRBYP ; 
 scalar_t__ PLL_INFF_MAX_RATE_HZ ; 
 scalar_t__ PLL_INFF_MIN_RATE_HZ ; 
 scalar_t__ STM32_USBPHYC_PLL ; 
 scalar_t__ clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  stm32_usbphyc_get_pll_params (scalar_t__,struct pll_params*) ; 
 int /*<<< orphan*/  writel_relaxed (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int stm32_usbphyc_pll_init(struct stm32_usbphyc *usbphyc)
{
	struct pll_params pll_params;
	u32 clk_rate = clk_get_rate(usbphyc->clk);
	u32 ndiv, frac;
	u32 usbphyc_pll;

	if ((clk_rate < PLL_INFF_MIN_RATE_HZ) ||
	    (clk_rate > PLL_INFF_MAX_RATE_HZ)) {
		dev_err(usbphyc->dev, "input clk freq (%dHz) out of range\n",
			clk_rate);
		return -EINVAL;
	}

	stm32_usbphyc_get_pll_params(clk_rate, &pll_params);
	ndiv = FIELD_PREP(PLLNDIV, pll_params.ndiv);
	frac = FIELD_PREP(PLLFRACIN, pll_params.frac);

	usbphyc_pll = PLLDITHEN1 | PLLDITHEN0 | PLLSTRBYP | ndiv;

	if (pll_params.frac)
		usbphyc_pll |= PLLFRACCTL | frac;

	writel_relaxed(usbphyc_pll, usbphyc->base + STM32_USBPHYC_PLL);

	dev_dbg(usbphyc->dev, "input clk freq=%dHz, ndiv=%lu, frac=%lu\n",
		clk_rate, FIELD_GET(PLLNDIV, usbphyc_pll),
		FIELD_GET(PLLFRACIN, usbphyc_pll));

	return 0;
}