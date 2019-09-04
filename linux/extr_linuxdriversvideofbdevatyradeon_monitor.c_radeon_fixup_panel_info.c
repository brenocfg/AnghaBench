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
struct radeonfb_info {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void radeon_fixup_panel_info(struct radeonfb_info *rinfo)
{
#ifdef CONFIG_PPC
	/*
	 * LCD Flat panels should use fixed dividers, we enfore that on
	 * PPC only for now...
	 */
	if (!rinfo->panel_info.use_bios_dividers && rinfo->mon1_type == MT_LCD
	    && rinfo->is_mobility) {
		int ppll_div_sel;
		u32 ppll_divn;
		ppll_div_sel = INREG8(CLOCK_CNTL_INDEX + 1) & 0x3;
		radeon_pll_errata_after_index(rinfo);
		ppll_divn = INPLL(PPLL_DIV_0 + ppll_div_sel);
		rinfo->panel_info.ref_divider = rinfo->pll.ref_div;
		rinfo->panel_info.fbk_divider = ppll_divn & 0x7ff;
		rinfo->panel_info.post_divider = (ppll_divn >> 16) & 0x7;
		rinfo->panel_info.use_bios_dividers = 1;

		printk(KERN_DEBUG "radeonfb: Using Firmware dividers 0x%08x "
		       "from PPLL %d\n",
		       rinfo->panel_info.fbk_divider |
		       (rinfo->panel_info.post_divider << 16),
		       ppll_div_sel);
	}
#endif /* CONFIG_PPC */
}