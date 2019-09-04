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
typedef  int u8 ;
typedef  int u32 ;
struct pll_ct {int vclk_post_div_real; int xclk_ref_div; int xclkmaxrasdelay; int xclk_post_div; int fifo_size; int xclkpagefaultdelay; int dsp_on_off; int dsp_config; int dsp_loop_latency; scalar_t__ vclk_fb_div; scalar_t__ mclk_fb_div; } ;
struct fb_info {int dummy; } ;
typedef  int s8 ;

/* Variables and functions */
 int Maximum_DSP_PRECISION ; 

__attribute__((used)) static int aty_dsp_gt(const struct fb_info *info, u32 bpp, struct pll_ct *pll)
{
	u32 dsp_off, dsp_on, dsp_xclks;
	u32 multiplier, divider, ras_multiplier, ras_divider, tmp;
	u8 vshift, xshift;
	s8 dsp_precision;

	multiplier = ((u32)pll->mclk_fb_div) * pll->vclk_post_div_real;
	divider = ((u32)pll->vclk_fb_div) * pll->xclk_ref_div;

	ras_multiplier = pll->xclkmaxrasdelay;
	ras_divider = 1;

	if (bpp>=8)
		divider = divider * (bpp >> 2);

	vshift = (6 - 2) - pll->xclk_post_div;	/* FIFO is 64 bits wide in accelerator mode ... */

	if (bpp == 0)
		vshift--;	/* ... but only 32 bits in VGA mode. */

#ifdef CONFIG_FB_ATY_GENERIC_LCD
	if (pll->xres != 0) {
		struct atyfb_par *par = (struct atyfb_par *) info->par;

		multiplier = multiplier * par->lcd_width;
		divider = divider * pll->xres & ~7;

		ras_multiplier = ras_multiplier * par->lcd_width;
		ras_divider = ras_divider * pll->xres & ~7;
	}
#endif
	/* If we don't do this, 32 bits for multiplier & divider won't be
	enough in certain situations! */
	while (((multiplier | divider) & 1) == 0) {
		multiplier = multiplier >> 1;
		divider = divider >> 1;
	}

	/* Determine DSP precision first */
	tmp = ((multiplier * pll->fifo_size) << vshift) / divider;

	for (dsp_precision = -5;  tmp;  dsp_precision++)
		tmp >>= 1;
	if (dsp_precision < 0)
		dsp_precision = 0;
	else if (dsp_precision > Maximum_DSP_PRECISION)
		dsp_precision = Maximum_DSP_PRECISION;

	xshift = 6 - dsp_precision;
	vshift += xshift;

	/* Move on to dsp_off */
	dsp_off = ((multiplier * (pll->fifo_size - 1)) << vshift) / divider -
		(1 << (vshift - xshift));

/*    if (bpp == 0)
        dsp_on = ((multiplier * 20 << vshift) + divider) / divider;
    else */
	{
		dsp_on = ((multiplier << vshift) + divider) / divider;
		tmp = ((ras_multiplier << xshift) + ras_divider) / ras_divider;
		if (dsp_on < tmp)
			dsp_on = tmp;
		dsp_on = dsp_on + (tmp * 2) + (pll->xclkpagefaultdelay << xshift);
	}

	/* Calculate rounding factor and apply it to dsp_on */
	tmp = ((1 << (Maximum_DSP_PRECISION - dsp_precision)) - 1) >> 1;
	dsp_on = ((dsp_on + tmp) / (tmp + 1)) * (tmp + 1);

	if (dsp_on >= ((dsp_off / (tmp + 1)) * (tmp + 1))) {
		dsp_on = dsp_off - (multiplier << vshift) / divider;
		dsp_on = (dsp_on / (tmp + 1)) * (tmp + 1);
	}

	/* Last but not least:  dsp_xclks */
	dsp_xclks = ((multiplier << (vshift + 5)) + divider) / divider;

	/* Get register values. */
	pll->dsp_on_off = (dsp_on << 16) + dsp_off;
	pll->dsp_config = (dsp_precision << 20) | (pll->dsp_loop_latency << 16) | dsp_xclks;
#ifdef DEBUG
	printk("atyfb(%s): dsp_config 0x%08x, dsp_on_off 0x%08x\n",
		__func__, pll->dsp_config, pll->dsp_on_off);
#endif
	return 0;
}