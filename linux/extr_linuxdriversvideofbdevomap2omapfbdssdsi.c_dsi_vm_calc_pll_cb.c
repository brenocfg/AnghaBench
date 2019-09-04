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
struct TYPE_2__ {int n; int m; unsigned long fint; unsigned long clkdco; } ;
struct dsi_clk_calc_ctx {int /*<<< orphan*/  req_pck_min; int /*<<< orphan*/  pll; TYPE_1__ dsi_cinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  FEAT_PARAM_DSS_FCK ; 
 int /*<<< orphan*/  dsi_vm_calc_hsdiv_cb ; 
 int /*<<< orphan*/  dss_feat_get_param_max (int /*<<< orphan*/ ) ; 
 int dss_pll_hsdiv_calc (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dsi_clk_calc_ctx*) ; 

__attribute__((used)) static bool dsi_vm_calc_pll_cb(int n, int m, unsigned long fint,
		unsigned long clkdco, void *data)
{
	struct dsi_clk_calc_ctx *ctx = data;

	ctx->dsi_cinfo.n = n;
	ctx->dsi_cinfo.m = m;
	ctx->dsi_cinfo.fint = fint;
	ctx->dsi_cinfo.clkdco = clkdco;

	return dss_pll_hsdiv_calc(ctx->pll, clkdco, ctx->req_pck_min,
			dss_feat_get_param_max(FEAT_PARAM_DSS_FCK),
			dsi_vm_calc_hsdiv_cb, ctx);
}