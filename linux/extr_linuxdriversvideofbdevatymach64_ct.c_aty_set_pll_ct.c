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
struct TYPE_2__ {int pll_vclk_cntl; int vclk_post_div; int pll_ext_cntl; int vclk_fb_div; int pll_gen_cntl; int dsp_config; int dsp_on_off; } ;
union aty_pll {TYPE_1__ ct; } ;
typedef  int u8 ;
typedef  int u32 ;
struct fb_info {scalar_t__ par; } ;
struct atyfb_par {int clk_wr_offset; scalar_t__ ram_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_CNTL ; 
 int CLOCK_STROBE ; 
 int CRTC_EXT_DISP_EN ; 
 int /*<<< orphan*/  CRTC_GEN_CNTL ; 
 int DLL_CNTL ; 
 int /*<<< orphan*/  DSP_CONFIG ; 
 int /*<<< orphan*/  DSP_ON_OFF ; 
 int /*<<< orphan*/  GTB_DSP ; 
 scalar_t__ M64_HAS (int /*<<< orphan*/ ) ; 
 int OSC_EN ; 
 int PLL_EXT_CNTL ; 
 int PLL_GEN_CNTL ; 
 int PLL_MCLK_RST ; 
 int PLL_OVERRIDE ; 
 int PLL_VCLK_CNTL ; 
 int PLL_VCLK_RST ; 
 scalar_t__ SDRAM ; 
 int VCLK0_FB_DIV ; 
 int VCLK_POST_DIV ; 
 int VFC_CNTL ; 
 int /*<<< orphan*/  XL_DLL ; 
 int aty_ld_le32 (int /*<<< orphan*/ ,struct atyfb_par*) ; 
 int aty_ld_pll_ct (int,struct atyfb_par*) ; 
 int /*<<< orphan*/  aty_st_8 (int /*<<< orphan*/ ,int,struct atyfb_par*) ; 
 int /*<<< orphan*/  aty_st_le32 (int /*<<< orphan*/ ,int,struct atyfb_par*) ; 
 int /*<<< orphan*/  aty_st_pll_ct (int,int,struct atyfb_par*) ; 
 int /*<<< orphan*/  mdelay (int) ; 

void aty_set_pll_ct(const struct fb_info *info, const union aty_pll *pll)
{
	struct atyfb_par *par = (struct atyfb_par *) info->par;
	u32 crtc_gen_cntl, lcd_gen_cntrl;
	u8 tmp, tmp2;

	lcd_gen_cntrl = 0;
#ifdef DEBUG
	printk("atyfb(%s): about to program:\n"
		"pll_ext_cntl=0x%02x pll_gen_cntl=0x%02x pll_vclk_cntl=0x%02x\n",
		__func__,
		pll->ct.pll_ext_cntl, pll->ct.pll_gen_cntl, pll->ct.pll_vclk_cntl);

	printk("atyfb(%s): setting clock %lu for FeedBackDivider %i, ReferenceDivider %i, PostDivider %i(%i)\n",
		__func__,
		par->clk_wr_offset, pll->ct.vclk_fb_div,
		pll->ct.pll_ref_div, pll->ct.vclk_post_div, pll->ct.vclk_post_div_real);
#endif
#ifdef CONFIG_FB_ATY_GENERIC_LCD
	if (par->lcd_table != 0) {
		/* turn off LCD */
		lcd_gen_cntrl = aty_ld_lcd(LCD_GEN_CNTL, par);
		aty_st_lcd(LCD_GEN_CNTL, lcd_gen_cntrl & ~LCD_ON, par);
	}
#endif
	aty_st_8(CLOCK_CNTL, par->clk_wr_offset | CLOCK_STROBE, par);

	/* Temporarily switch to accelerator mode */
	crtc_gen_cntl = aty_ld_le32(CRTC_GEN_CNTL, par);
	if (!(crtc_gen_cntl & CRTC_EXT_DISP_EN))
		aty_st_le32(CRTC_GEN_CNTL, crtc_gen_cntl | CRTC_EXT_DISP_EN, par);

	/* Reset VCLK generator */
	aty_st_pll_ct(PLL_VCLK_CNTL, pll->ct.pll_vclk_cntl, par);

	/* Set post-divider */
	tmp2 = par->clk_wr_offset << 1;
	tmp = aty_ld_pll_ct(VCLK_POST_DIV, par);
	tmp &= ~(0x03U << tmp2);
	tmp |= ((pll->ct.vclk_post_div & 0x03U) << tmp2);
	aty_st_pll_ct(VCLK_POST_DIV, tmp, par);

	/* Set extended post-divider */
	tmp = aty_ld_pll_ct(PLL_EXT_CNTL, par);
	tmp &= ~(0x10U << par->clk_wr_offset);
	tmp &= 0xF0U;
	tmp |= pll->ct.pll_ext_cntl;
	aty_st_pll_ct(PLL_EXT_CNTL, tmp, par);

	/* Set feedback divider */
	tmp = VCLK0_FB_DIV + par->clk_wr_offset;
	aty_st_pll_ct(tmp, (pll->ct.vclk_fb_div & 0xFFU), par);

	aty_st_pll_ct(PLL_GEN_CNTL, (pll->ct.pll_gen_cntl & (~(PLL_OVERRIDE | PLL_MCLK_RST))) | OSC_EN, par);

	/* End VCLK generator reset */
	aty_st_pll_ct(PLL_VCLK_CNTL, pll->ct.pll_vclk_cntl & ~(PLL_VCLK_RST), par);
	mdelay(5);

	aty_st_pll_ct(PLL_GEN_CNTL, pll->ct.pll_gen_cntl, par);
	aty_st_pll_ct(PLL_VCLK_CNTL, pll->ct.pll_vclk_cntl, par);
	mdelay(1);

	/* Restore mode register */
	if (!(crtc_gen_cntl & CRTC_EXT_DISP_EN))
		aty_st_le32(CRTC_GEN_CNTL, crtc_gen_cntl, par);

	if (M64_HAS(GTB_DSP)) {
		u8 dll_cntl;

		if (M64_HAS(XL_DLL))
			dll_cntl = 0x80;
		else if (par->ram_type >= SDRAM)
			dll_cntl = 0xa6;
		else
			dll_cntl = 0xa0;
		aty_st_pll_ct(DLL_CNTL, dll_cntl, par);
		aty_st_pll_ct(VFC_CNTL, 0x1b, par);
		aty_st_le32(DSP_CONFIG, pll->ct.dsp_config, par);
		aty_st_le32(DSP_ON_OFF, pll->ct.dsp_on_off, par);

		mdelay(10);
		aty_st_pll_ct(DLL_CNTL, dll_cntl, par);
		mdelay(10);
		aty_st_pll_ct(DLL_CNTL, dll_cntl | 0x40, par);
		mdelay(10);
		aty_st_pll_ct(DLL_CNTL, dll_cntl & ~0x40, par);
	}
#ifdef CONFIG_FB_ATY_GENERIC_LCD
	if (par->lcd_table != 0) {
		/* restore LCD */
		aty_st_lcd(LCD_GEN_CNTL, lcd_gen_cntrl, par);
	}
#endif
}