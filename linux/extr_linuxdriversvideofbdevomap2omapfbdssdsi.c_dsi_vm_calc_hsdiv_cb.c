#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* mX; unsigned long* clkout; } ;
struct dsi_clk_calc_ctx {int req_pck_max; int /*<<< orphan*/  req_pck_min; TYPE_2__* config; TYPE_1__ dsi_cinfo; } ;
struct TYPE_4__ {scalar_t__ trans_mode; } ;

/* Variables and functions */
 size_t HSDIV_DISPC ; 
 scalar_t__ OMAP_DSS_DSI_BURST_MODE ; 
 int dispc_div_calc (unsigned long,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,struct dsi_clk_calc_ctx*) ; 
 int /*<<< orphan*/  dsi_vm_calc_dispc_cb ; 

__attribute__((used)) static bool dsi_vm_calc_hsdiv_cb(int m_dispc, unsigned long dispc,
		void *data)
{
	struct dsi_clk_calc_ctx *ctx = data;
	unsigned long pck_max;

	ctx->dsi_cinfo.mX[HSDIV_DISPC] = m_dispc;
	ctx->dsi_cinfo.clkout[HSDIV_DISPC] = dispc;

	/*
	 * In burst mode we can let the dispc pck be arbitrarily high, but it
	 * limits our scaling abilities. So for now, don't aim too high.
	 */

	if (ctx->config->trans_mode == OMAP_DSS_DSI_BURST_MODE)
		pck_max = ctx->req_pck_max + 10000000;
	else
		pck_max = ctx->req_pck_max;

	return dispc_div_calc(dispc, ctx->req_pck_min, pck_max,
			dsi_vm_calc_dispc_cb, ctx);
}