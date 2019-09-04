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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {unsigned long* clkout; } ;
struct dss_pll {TYPE_1__ cinfo; } ;
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  DISPC_DIVISORo (int) ; 
 int FLD_GET (int /*<<< orphan*/ ,int,int) ; 
#define  OMAP_DSS_CLK_SRC_DSI2_PLL_HSDIV_DISPC 130 
#define  OMAP_DSS_CLK_SRC_DSI_PLL_HSDIV_DISPC 129 
#define  OMAP_DSS_CLK_SRC_FCK 128 
 unsigned long dispc_fclk_rate () ; 
 int /*<<< orphan*/  dispc_read_reg (int /*<<< orphan*/ ) ; 
 unsigned long dss_get_dispc_clk_rate () ; 
 int dss_get_lcd_clk_source (int) ; 
 scalar_t__ dss_mgr_is_lcd (int) ; 
 struct dss_pll* dss_pll_find (char*) ; 

__attribute__((used)) static unsigned long dispc_mgr_lclk_rate(enum omap_channel channel)
{
	struct dss_pll *pll;
	int lcd;
	unsigned long r;
	u32 l;

	if (dss_mgr_is_lcd(channel)) {
		l = dispc_read_reg(DISPC_DIVISORo(channel));

		lcd = FLD_GET(l, 23, 16);

		switch (dss_get_lcd_clk_source(channel)) {
		case OMAP_DSS_CLK_SRC_FCK:
			r = dss_get_dispc_clk_rate();
			break;
		case OMAP_DSS_CLK_SRC_DSI_PLL_HSDIV_DISPC:
			pll = dss_pll_find("dsi0");
			if (!pll)
				pll = dss_pll_find("video0");

			r = pll->cinfo.clkout[0];
			break;
		case OMAP_DSS_CLK_SRC_DSI2_PLL_HSDIV_DISPC:
			pll = dss_pll_find("dsi1");
			if (!pll)
				pll = dss_pll_find("video1");

			r = pll->cinfo.clkout[0];
			break;
		default:
			BUG();
			return 0;
		}

		return r / lcd;
	} else {
		return dispc_fclk_rate();
	}
}