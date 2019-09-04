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
struct TYPE_2__ {int* mX; unsigned long* clkout; } ;
struct dpi_clk_calc_ctx {int pck_min; int /*<<< orphan*/  pck_max; TYPE_1__ dsi_cinfo; } ;

/* Variables and functions */
 size_t HSDIV_DISPC ; 
 int dispc_div_calc (unsigned long,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dpi_clk_calc_ctx*) ; 
 int /*<<< orphan*/  dpi_calc_dispc_cb ; 

__attribute__((used)) static bool dpi_calc_hsdiv_cb(int m_dispc, unsigned long dispc,
		void *data)
{
	struct dpi_clk_calc_ctx *ctx = data;

	/*
	 * Odd dividers give us uneven duty cycle, causing problem when level
	 * shifted. So skip all odd dividers when the pixel clock is on the
	 * higher side.
	 */
	if (m_dispc > 1 && m_dispc % 2 != 0 && ctx->pck_min >= 100000000)
		return false;

	ctx->dsi_cinfo.mX[HSDIV_DISPC] = m_dispc;
	ctx->dsi_cinfo.clkout[HSDIV_DISPC] = dispc;

	return dispc_div_calc(dispc, ctx->pck_min, ctx->pck_max,
			dpi_calc_dispc_cb, ctx);
}