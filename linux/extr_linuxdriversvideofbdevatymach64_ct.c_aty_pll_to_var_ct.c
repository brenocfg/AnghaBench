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
struct TYPE_2__ {int pll_ref_div; int vclk_post_div_real; int vclk_fb_div; } ;
union aty_pll {TYPE_1__ ct; } ;
typedef  int u32 ;
struct fb_info {scalar_t__ par; } ;
struct atyfb_par {int ref_clk_per; } ;

/* Variables and functions */

__attribute__((used)) static u32 aty_pll_to_var_ct(const struct fb_info *info, const union aty_pll *pll)
{
	struct atyfb_par *par = (struct atyfb_par *) info->par;
	u32 ret;
	ret = par->ref_clk_per * pll->ct.pll_ref_div * pll->ct.vclk_post_div_real / pll->ct.vclk_fb_div / 2;
#ifdef CONFIG_FB_ATY_GENERIC_LCD
	if(pll->ct.xres > 0) {
		ret *= par->lcd_width;
		ret /= pll->ct.xres;
	}
#endif
#ifdef DEBUG
	printk("atyfb(%s): calculated 0x%08X(%i)\n", __func__, ret, ret);
#endif
	return ret;
}