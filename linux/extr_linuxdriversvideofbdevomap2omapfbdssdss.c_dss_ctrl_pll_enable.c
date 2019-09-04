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
typedef  enum dss_pll_id { ____Placeholder_dss_pll_id } dss_pll_id ;
struct TYPE_2__ {int /*<<< orphan*/  syscon_pll_ctrl_offset; int /*<<< orphan*/  syscon_pll_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSERR (char*,int) ; 
#define  DSS_PLL_HDMI 130 
#define  DSS_PLL_VIDEO1 129 
#define  DSS_PLL_VIDEO2 128 
 TYPE_1__ dss ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int) ; 

void dss_ctrl_pll_enable(enum dss_pll_id pll_id, bool enable)
{
	unsigned shift;
	unsigned val;

	if (!dss.syscon_pll_ctrl)
		return;

	val = !enable;

	switch (pll_id) {
	case DSS_PLL_VIDEO1:
		shift = 0;
		break;
	case DSS_PLL_VIDEO2:
		shift = 1;
		break;
	case DSS_PLL_HDMI:
		shift = 2;
		break;
	default:
		DSSERR("illegal DSS PLL ID %d\n", pll_id);
		return;
	}

	regmap_update_bits(dss.syscon_pll_ctrl, dss.syscon_pll_ctrl_offset,
		1 << shift, val << shift);
}