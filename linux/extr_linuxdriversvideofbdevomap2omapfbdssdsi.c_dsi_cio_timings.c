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
typedef  int u32 ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_DSIPHY_CFG0 ; 
 int /*<<< orphan*/  DSI_DSIPHY_CFG1 ; 
 int /*<<< orphan*/  DSI_DSIPHY_CFG2 ; 
 int /*<<< orphan*/  DSSDBG (char*,int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  FEAT_DSI_PHY_DCC ; 
 int FLD_MOD (int,int,int,int) ; 
 int /*<<< orphan*/  ddr2ns (struct platform_device*,int) ; 
 int dsi_read_reg (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsi_write_reg (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ dss_has_feature (int /*<<< orphan*/ ) ; 
 int ns2ddr (struct platform_device*,int) ; 

__attribute__((used)) static void dsi_cio_timings(struct platform_device *dsidev)
{
	u32 r;
	u32 ths_prepare, ths_prepare_ths_zero, ths_trail, ths_exit;
	u32 tlpx_half, tclk_trail, tclk_zero;
	u32 tclk_prepare;

	/* calculate timings */

	/* 1 * DDR_CLK = 2 * UI */

	/* min 40ns + 4*UI	max 85ns + 6*UI */
	ths_prepare = ns2ddr(dsidev, 70) + 2;

	/* min 145ns + 10*UI */
	ths_prepare_ths_zero = ns2ddr(dsidev, 175) + 2;

	/* min max(8*UI, 60ns+4*UI) */
	ths_trail = ns2ddr(dsidev, 60) + 5;

	/* min 100ns */
	ths_exit = ns2ddr(dsidev, 145);

	/* tlpx min 50n */
	tlpx_half = ns2ddr(dsidev, 25);

	/* min 60ns */
	tclk_trail = ns2ddr(dsidev, 60) + 2;

	/* min 38ns, max 95ns */
	tclk_prepare = ns2ddr(dsidev, 65);

	/* min tclk-prepare + tclk-zero = 300ns */
	tclk_zero = ns2ddr(dsidev, 260);

	DSSDBG("ths_prepare %u (%uns), ths_prepare_ths_zero %u (%uns)\n",
		ths_prepare, ddr2ns(dsidev, ths_prepare),
		ths_prepare_ths_zero, ddr2ns(dsidev, ths_prepare_ths_zero));
	DSSDBG("ths_trail %u (%uns), ths_exit %u (%uns)\n",
			ths_trail, ddr2ns(dsidev, ths_trail),
			ths_exit, ddr2ns(dsidev, ths_exit));

	DSSDBG("tlpx_half %u (%uns), tclk_trail %u (%uns), "
			"tclk_zero %u (%uns)\n",
			tlpx_half, ddr2ns(dsidev, tlpx_half),
			tclk_trail, ddr2ns(dsidev, tclk_trail),
			tclk_zero, ddr2ns(dsidev, tclk_zero));
	DSSDBG("tclk_prepare %u (%uns)\n",
			tclk_prepare, ddr2ns(dsidev, tclk_prepare));

	/* program timings */

	r = dsi_read_reg(dsidev, DSI_DSIPHY_CFG0);
	r = FLD_MOD(r, ths_prepare, 31, 24);
	r = FLD_MOD(r, ths_prepare_ths_zero, 23, 16);
	r = FLD_MOD(r, ths_trail, 15, 8);
	r = FLD_MOD(r, ths_exit, 7, 0);
	dsi_write_reg(dsidev, DSI_DSIPHY_CFG0, r);

	r = dsi_read_reg(dsidev, DSI_DSIPHY_CFG1);
	r = FLD_MOD(r, tlpx_half, 20, 16);
	r = FLD_MOD(r, tclk_trail, 15, 8);
	r = FLD_MOD(r, tclk_zero, 7, 0);

	if (dss_has_feature(FEAT_DSI_PHY_DCC)) {
		r = FLD_MOD(r, 0, 21, 21);	/* DCCEN = disable */
		r = FLD_MOD(r, 1, 22, 22);	/* CLKINP_DIVBY2EN = enable */
		r = FLD_MOD(r, 1, 23, 23);	/* CLKINP_SEL = enable */
	}

	dsi_write_reg(dsidev, DSI_DSIPHY_CFG1, r);

	r = dsi_read_reg(dsidev, DSI_DSIPHY_CFG2);
	r = FLD_MOD(r, tclk_prepare, 7, 0);
	dsi_write_reg(dsidev, DSI_DSIPHY_CFG2, r);
}