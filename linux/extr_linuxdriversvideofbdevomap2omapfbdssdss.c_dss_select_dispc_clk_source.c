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
typedef  int /*<<< orphan*/  u8 ;
typedef  enum omap_dss_clk_source { ____Placeholder_omap_dss_clk_source } omap_dss_clk_source ;
struct TYPE_2__ {int dispc_clk_source; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  DSS_CONTROL ; 
 int /*<<< orphan*/  FEAT_REG_DISPC_CLK_SWITCH ; 
#define  OMAP_DSS_CLK_SRC_DSI2_PLL_HSDIV_DISPC 130 
#define  OMAP_DSS_CLK_SRC_DSI_PLL_HSDIV_DISPC 129 
#define  OMAP_DSS_CLK_SRC_FCK 128 
 int /*<<< orphan*/  REG_FLD_MOD (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ dss ; 
 int /*<<< orphan*/  dss_feat_get_reg_field (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dss_select_dispc_clk_source(enum omap_dss_clk_source clk_src)
{
	int b;
	u8 start, end;

	switch (clk_src) {
	case OMAP_DSS_CLK_SRC_FCK:
		b = 0;
		break;
	case OMAP_DSS_CLK_SRC_DSI_PLL_HSDIV_DISPC:
		b = 1;
		break;
	case OMAP_DSS_CLK_SRC_DSI2_PLL_HSDIV_DISPC:
		b = 2;
		break;
	default:
		BUG();
		return;
	}

	dss_feat_get_reg_field(FEAT_REG_DISPC_CLK_SWITCH, &start, &end);

	REG_FLD_MOD(DSS_CONTROL, b, start, end);	/* DISPC_CLK_SWITCH */

	dss.dispc_clk_source = clk_src;
}