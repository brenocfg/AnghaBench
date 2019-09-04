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
struct s3c2410fb_info {int /*<<< orphan*/  dev; } ;
struct s3c2410fb_hw {int lcdcon1; int lcdcon3; int /*<<< orphan*/  lcdcon4; int /*<<< orphan*/  lcdcon2; } ;
struct fb_var_screeninfo {int xres; int left_margin; int hsync_len; int bits_per_pixel; int right_margin; scalar_t__ yres; } ;
struct fb_info {struct fb_var_screeninfo var; struct s3c2410fb_info* par; } ;

/* Variables and functions */
 int S3C2410_LCDCON1_STN12BPP ; 
 int S3C2410_LCDCON1_STN1BPP ; 
 int S3C2410_LCDCON1_STN2GREY ; 
 int S3C2410_LCDCON1_STN4 ; 
 int S3C2410_LCDCON1_STN4GREY ; 
 int S3C2410_LCDCON1_STN8BPP ; 
 int S3C2410_LCDCON1_TFT ; 
 int /*<<< orphan*/  S3C2410_LCDCON2_LINEVAL (scalar_t__) ; 
 int S3C2410_LCDCON3_HOZVAL (int) ; 
 int S3C2410_LCDCON3_LINEBLANK (int) ; 
 int S3C2410_LCDCON3_WDLY (unsigned int) ; 
 int /*<<< orphan*/  S3C2410_LCDCON4_WLH (unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dprintk (char*,int,int,int) ; 

__attribute__((used)) static void s3c2410fb_calculate_stn_lcd_regs(const struct fb_info *info,
					     struct s3c2410fb_hw *regs)
{
	const struct s3c2410fb_info *fbi = info->par;
	const struct fb_var_screeninfo *var = &info->var;
	int type = regs->lcdcon1 & ~S3C2410_LCDCON1_TFT;
	int hs = var->xres >> 2;
	unsigned wdly = (var->left_margin >> 4) - 1;
	unsigned wlh = (var->hsync_len >> 4) - 1;

	if (type != S3C2410_LCDCON1_STN4)
		hs >>= 1;

	switch (var->bits_per_pixel) {
	case 1:
		regs->lcdcon1 |= S3C2410_LCDCON1_STN1BPP;
		break;
	case 2:
		regs->lcdcon1 |= S3C2410_LCDCON1_STN2GREY;
		break;
	case 4:
		regs->lcdcon1 |= S3C2410_LCDCON1_STN4GREY;
		break;
	case 8:
		regs->lcdcon1 |= S3C2410_LCDCON1_STN8BPP;
		hs *= 3;
		break;
	case 12:
		regs->lcdcon1 |= S3C2410_LCDCON1_STN12BPP;
		hs *= 3;
		break;

	default:
		/* invalid pixel depth */
		dev_err(fbi->dev, "invalid bpp %d\n",
			var->bits_per_pixel);
	}
	/* update X/Y info */
	dprintk("setting horz: lft=%d, rt=%d, sync=%d\n",
		var->left_margin, var->right_margin, var->hsync_len);

	regs->lcdcon2 = S3C2410_LCDCON2_LINEVAL(var->yres - 1);

	if (wdly > 3)
		wdly = 3;

	if (wlh > 3)
		wlh = 3;

	regs->lcdcon3 =	S3C2410_LCDCON3_WDLY(wdly) |
			S3C2410_LCDCON3_LINEBLANK(var->right_margin / 8) |
			S3C2410_LCDCON3_HOZVAL(hs - 1);

	regs->lcdcon4 = S3C2410_LCDCON4_WLH(wlh);
}