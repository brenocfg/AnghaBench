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
struct geodefb_par {scalar_t__ panel_x; scalar_t__ vid_regs; scalar_t__ enable_crt; } ;
struct fb_info {struct geodefb_par* par; } ;

/* Variables and functions */
 int CS5530_DCFG_DAC_BL_EN ; 
 int CS5530_DCFG_DAC_PWR_EN ; 
 int CS5530_DCFG_FP_DATA_EN ; 
 int CS5530_DCFG_FP_PWR_EN ; 
 int CS5530_DCFG_HSYNC_EN ; 
 int CS5530_DCFG_VSYNC_EN ; 
 scalar_t__ CS5530_DISPLAY_CONFIG ; 
 int EINVAL ; 
#define  FB_BLANK_HSYNC_SUSPEND 132 
#define  FB_BLANK_NORMAL 131 
#define  FB_BLANK_POWERDOWN 130 
#define  FB_BLANK_UNBLANK 129 
#define  FB_BLANK_VSYNC_SUSPEND 128 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int cs5530_blank_display(struct fb_info *info, int blank_mode)
{
	struct geodefb_par *par = info->par;
	u32 dcfg;
	int blank, hsync, vsync;

	switch (blank_mode) {
	case FB_BLANK_UNBLANK:
		blank = 0; hsync = 1; vsync = 1;
		break;
	case FB_BLANK_NORMAL:
		blank = 1; hsync = 1; vsync = 1;
		break;
	case FB_BLANK_VSYNC_SUSPEND:
		blank = 1; hsync = 1; vsync = 0;
		break;
	case FB_BLANK_HSYNC_SUSPEND:
		blank = 1; hsync = 0; vsync = 1;
		break;
	case FB_BLANK_POWERDOWN:
		blank = 1; hsync = 0; vsync = 0;
		break;
	default:
		return -EINVAL;
	}

	dcfg = readl(par->vid_regs + CS5530_DISPLAY_CONFIG);

	dcfg &= ~(CS5530_DCFG_DAC_BL_EN | CS5530_DCFG_DAC_PWR_EN
		  | CS5530_DCFG_HSYNC_EN | CS5530_DCFG_VSYNC_EN
		  | CS5530_DCFG_FP_DATA_EN | CS5530_DCFG_FP_PWR_EN);

	if (par->enable_crt) {
		if (!blank)
			dcfg |= CS5530_DCFG_DAC_BL_EN | CS5530_DCFG_DAC_PWR_EN;
		if (hsync)
			dcfg |= CS5530_DCFG_HSYNC_EN;
		if (vsync)
			dcfg |= CS5530_DCFG_VSYNC_EN;
	}
	if (par->panel_x > 0) {
		if (!blank)
			dcfg |= CS5530_DCFG_FP_DATA_EN;
		if (hsync && vsync)
			dcfg |= CS5530_DCFG_FP_PWR_EN;
	}

	writel(dcfg, par->vid_regs + CS5530_DISPLAY_CONFIG);

	return 0;
}