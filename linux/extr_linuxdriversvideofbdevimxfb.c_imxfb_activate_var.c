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
typedef  int u32 ;
struct imxfb_info {int pcr; int pwmr; int lscr1; int dmacr; int lauscr; scalar_t__ regs; } ;
struct fb_var_screeninfo {int xres; int yres; int bits_per_pixel; scalar_t__ upper_margin; scalar_t__ lower_margin; scalar_t__ vsync_len; scalar_t__ left_margin; scalar_t__ right_margin; scalar_t__ hsync_len; } ;
struct fb_info {struct imxfb_info* par; } ;

/* Variables and functions */
 int HCR_H_WAIT_1 (scalar_t__) ; 
 int HCR_H_WAIT_2 (scalar_t__) ; 
 int HCR_H_WIDTH (scalar_t__) ; 
 scalar_t__ LCDC_DMACR ; 
 scalar_t__ LCDC_HCR ; 
 scalar_t__ LCDC_LAUSCR ; 
 scalar_t__ LCDC_LSCR1 ; 
 scalar_t__ LCDC_PCR ; 
 scalar_t__ LCDC_PWMR ; 
 scalar_t__ LCDC_SIZE ; 
 scalar_t__ LCDC_VCR ; 
 scalar_t__ LCDC_VPW ; 
 int SIZE_XMAX (int) ; 
 int VCR_V_WAIT_1 (scalar_t__) ; 
 int VCR_V_WAIT_2 (scalar_t__) ; 
 int VCR_V_WIDTH (scalar_t__) ; 
 int VPW_VPW (int) ; 
 int YMAX_MASK_IMX1 ; 
 int YMAX_MASK_IMX21 ; 
 scalar_t__ is_imx1_fb (struct imxfb_info*) ; 
 int /*<<< orphan*/  pr_debug (char*,int,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int imxfb_activate_var(struct fb_var_screeninfo *var, struct fb_info *info)
{
	struct imxfb_info *fbi = info->par;
	u32 ymax_mask = is_imx1_fb(fbi) ? YMAX_MASK_IMX1 : YMAX_MASK_IMX21;

	pr_debug("var: xres=%d hslen=%d lm=%d rm=%d\n",
		var->xres, var->hsync_len,
		var->left_margin, var->right_margin);
	pr_debug("var: yres=%d vslen=%d um=%d bm=%d\n",
		var->yres, var->vsync_len,
		var->upper_margin, var->lower_margin);

#if DEBUG_VAR
	if (var->xres < 16        || var->xres > 1024)
		printk(KERN_ERR "%s: invalid xres %d\n",
			info->fix.id, var->xres);
	if (var->hsync_len < 1    || var->hsync_len > 64)
		printk(KERN_ERR "%s: invalid hsync_len %d\n",
			info->fix.id, var->hsync_len);
	if (var->left_margin > 255)
		printk(KERN_ERR "%s: invalid left_margin %d\n",
			info->fix.id, var->left_margin);
	if (var->right_margin > 255)
		printk(KERN_ERR "%s: invalid right_margin %d\n",
			info->fix.id, var->right_margin);
	if (var->yres < 1 || var->yres > ymax_mask)
		printk(KERN_ERR "%s: invalid yres %d\n",
			info->fix.id, var->yres);
	if (var->vsync_len > 100)
		printk(KERN_ERR "%s: invalid vsync_len %d\n",
			info->fix.id, var->vsync_len);
	if (var->upper_margin > 63)
		printk(KERN_ERR "%s: invalid upper_margin %d\n",
			info->fix.id, var->upper_margin);
	if (var->lower_margin > 255)
		printk(KERN_ERR "%s: invalid lower_margin %d\n",
			info->fix.id, var->lower_margin);
#endif

	/* physical screen start address	    */
	writel(VPW_VPW(var->xres * var->bits_per_pixel / 8 / 4),
		fbi->regs + LCDC_VPW);

	writel(HCR_H_WIDTH(var->hsync_len - 1) |
		HCR_H_WAIT_1(var->right_margin - 1) |
		HCR_H_WAIT_2(var->left_margin - 3),
		fbi->regs + LCDC_HCR);

	writel(VCR_V_WIDTH(var->vsync_len) |
		VCR_V_WAIT_1(var->lower_margin) |
		VCR_V_WAIT_2(var->upper_margin),
		fbi->regs + LCDC_VCR);

	writel(SIZE_XMAX(var->xres) | (var->yres & ymax_mask),
			fbi->regs + LCDC_SIZE);

	writel(fbi->pcr, fbi->regs + LCDC_PCR);
	if (fbi->pwmr)
		writel(fbi->pwmr, fbi->regs + LCDC_PWMR);
	writel(fbi->lscr1, fbi->regs + LCDC_LSCR1);

	/* dmacr = 0 is no valid value, as we need DMA control marks. */
	if (fbi->dmacr)
		writel(fbi->dmacr, fbi->regs + LCDC_DMACR);

	if (fbi->lauscr)
		writel(fbi->lauscr, fbi->regs + LCDC_LAUSCR);

	return 0;
}