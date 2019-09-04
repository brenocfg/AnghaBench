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
struct dpi_data {TYPE_1__* pll; } ;
struct dpi_clk_calc_ctx {unsigned long pck_min; unsigned long pck_max; TYPE_1__* pll; } ;
struct TYPE_2__ {int /*<<< orphan*/  clkin; } ;

/* Variables and functions */
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpi_calc_pll_cb ; 
 int dss_pll_calc (TYPE_1__*,unsigned long,unsigned long,unsigned long,int /*<<< orphan*/ ,struct dpi_clk_calc_ctx*) ; 
 int /*<<< orphan*/  memset (struct dpi_clk_calc_ctx*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool dpi_dsi_clk_calc(struct dpi_data *dpi, unsigned long pck,
		struct dpi_clk_calc_ctx *ctx)
{
	unsigned long clkin;
	unsigned long pll_min, pll_max;

	memset(ctx, 0, sizeof(*ctx));
	ctx->pll = dpi->pll;
	ctx->pck_min = pck - 1000;
	ctx->pck_max = pck + 1000;

	pll_min = 0;
	pll_max = 0;

	clkin = clk_get_rate(ctx->pll->clkin);

	return dss_pll_calc(ctx->pll, clkin,
			pll_min, pll_max,
			dpi_calc_pll_cb, ctx);
}