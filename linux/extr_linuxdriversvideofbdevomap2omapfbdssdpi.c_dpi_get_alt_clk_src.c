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
typedef  enum omap_dss_clk_source { ____Placeholder_omap_dss_clk_source } omap_dss_clk_source ;
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;

/* Variables and functions */
#define  OMAP_DSS_CHANNEL_LCD 130 
#define  OMAP_DSS_CHANNEL_LCD2 129 
#define  OMAP_DSS_CHANNEL_LCD3 128 
 int OMAP_DSS_CLK_SRC_DSI2_PLL_HSDIV_DISPC ; 
 int OMAP_DSS_CLK_SRC_DSI_PLL_HSDIV_DISPC ; 
 int OMAP_DSS_CLK_SRC_FCK ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static enum omap_dss_clk_source dpi_get_alt_clk_src(enum omap_channel channel)
{
	switch (channel) {
	case OMAP_DSS_CHANNEL_LCD:
		return OMAP_DSS_CLK_SRC_DSI_PLL_HSDIV_DISPC;
	case OMAP_DSS_CHANNEL_LCD2:
		return OMAP_DSS_CLK_SRC_DSI2_PLL_HSDIV_DISPC;
	case OMAP_DSS_CHANNEL_LCD3:
		return OMAP_DSS_CLK_SRC_DSI2_PLL_HSDIV_DISPC;
	default:
		/* this shouldn't happen */
		WARN_ON(1);
		return OMAP_DSS_CLK_SRC_FCK;
	}
}