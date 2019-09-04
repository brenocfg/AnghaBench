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
struct dss_pll_clock_info {int* mX; int clkdco; int* clkout; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,unsigned long) ; 
 int /*<<< orphan*/  FEAT_PARAM_DSI_FCK ; 
 size_t HSDIV_DSI ; 
 unsigned long dss_feat_get_param_max (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dsi_pll_calc_dsi_fck(struct dss_pll_clock_info *cinfo)
{
	unsigned long max_dsi_fck;

	max_dsi_fck = dss_feat_get_param_max(FEAT_PARAM_DSI_FCK);

	cinfo->mX[HSDIV_DSI] = DIV_ROUND_UP(cinfo->clkdco, max_dsi_fck);
	cinfo->clkout[HSDIV_DSI] = cinfo->clkdco / cinfo->mX[HSDIV_DSI];
}