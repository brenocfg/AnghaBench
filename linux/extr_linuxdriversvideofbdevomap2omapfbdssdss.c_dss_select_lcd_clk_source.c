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
typedef  enum omap_dss_clk_source { ____Placeholder_omap_dss_clk_source } omap_dss_clk_source ;
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;
struct TYPE_2__ {int* lcd_clk_source; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DSS_CONTROL ; 
 int /*<<< orphan*/  FEAT_LCD_CLK_SRC ; 
 int OMAP_DSS_CHANNEL_LCD ; 
 int OMAP_DSS_CHANNEL_LCD2 ; 
 int OMAP_DSS_CHANNEL_LCD3 ; 
#define  OMAP_DSS_CLK_SRC_DSI2_PLL_HSDIV_DISPC 130 
#define  OMAP_DSS_CLK_SRC_DSI_PLL_HSDIV_DISPC 129 
#define  OMAP_DSS_CLK_SRC_FCK 128 
 int /*<<< orphan*/  REG_FLD_MOD (int /*<<< orphan*/ ,int,int,int) ; 
 TYPE_1__ dss ; 
 int /*<<< orphan*/  dss_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dss_select_dispc_clk_source (int) ; 

void dss_select_lcd_clk_source(enum omap_channel channel,
		enum omap_dss_clk_source clk_src)
{
	int b, ix, pos;

	if (!dss_has_feature(FEAT_LCD_CLK_SRC)) {
		dss_select_dispc_clk_source(clk_src);
		return;
	}

	switch (clk_src) {
	case OMAP_DSS_CLK_SRC_FCK:
		b = 0;
		break;
	case OMAP_DSS_CLK_SRC_DSI_PLL_HSDIV_DISPC:
		BUG_ON(channel != OMAP_DSS_CHANNEL_LCD);
		b = 1;
		break;
	case OMAP_DSS_CLK_SRC_DSI2_PLL_HSDIV_DISPC:
		BUG_ON(channel != OMAP_DSS_CHANNEL_LCD2 &&
		       channel != OMAP_DSS_CHANNEL_LCD3);
		b = 1;
		break;
	default:
		BUG();
		return;
	}

	pos = channel == OMAP_DSS_CHANNEL_LCD ? 0 :
	     (channel == OMAP_DSS_CHANNEL_LCD2 ? 12 : 19);
	REG_FLD_MOD(DSS_CONTROL, b, pos, pos);	/* LCDx_CLK_SWITCH */

	ix = channel == OMAP_DSS_CHANNEL_LCD ? 0 :
	    (channel == OMAP_DSS_CHANNEL_LCD2 ? 1 : 2);
	dss.lcd_clk_source[ix] = clk_src;
}