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
struct gxfb_par {scalar_t__ enable_crt; } ;
struct fb_info {struct gxfb_par* par; } ;

/* Variables and functions */
 int EINVAL ; 
#define  FB_BLANK_HSYNC_SUSPEND 132 
#define  FB_BLANK_NORMAL 131 
#define  FB_BLANK_POWERDOWN 130 
#define  FB_BLANK_UNBLANK 129 
#define  FB_BLANK_VSYNC_SUSPEND 128 
 int /*<<< orphan*/  FP_PM ; 
 int FP_PM_P ; 
 int /*<<< orphan*/  VP_DCFG ; 
 int VP_DCFG_CRT_EN ; 
 int VP_DCFG_DAC_BL_EN ; 
 int VP_DCFG_HSYNC_EN ; 
 int VP_DCFG_VSYNC_EN ; 
 int read_fp (struct gxfb_par*,int /*<<< orphan*/ ) ; 
 int read_vp (struct gxfb_par*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_fp (struct gxfb_par*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_vp (struct gxfb_par*,int /*<<< orphan*/ ,int) ; 

int gx_blank_display(struct fb_info *info, int blank_mode)
{
	struct gxfb_par *par = info->par;
	u32 dcfg, fp_pm;
	int blank, hsync, vsync, crt;

	/* CRT power saving modes. */
	switch (blank_mode) {
	case FB_BLANK_UNBLANK:
		blank = 0; hsync = 1; vsync = 1; crt = 1;
		break;
	case FB_BLANK_NORMAL:
		blank = 1; hsync = 1; vsync = 1; crt = 1;
		break;
	case FB_BLANK_VSYNC_SUSPEND:
		blank = 1; hsync = 1; vsync = 0; crt = 1;
		break;
	case FB_BLANK_HSYNC_SUSPEND:
		blank = 1; hsync = 0; vsync = 1; crt = 1;
		break;
	case FB_BLANK_POWERDOWN:
		blank = 1; hsync = 0; vsync = 0; crt = 0;
		break;
	default:
		return -EINVAL;
	}
	dcfg = read_vp(par, VP_DCFG);
	dcfg &= ~(VP_DCFG_DAC_BL_EN | VP_DCFG_HSYNC_EN | VP_DCFG_VSYNC_EN |
			VP_DCFG_CRT_EN);
	if (!blank)
		dcfg |= VP_DCFG_DAC_BL_EN;
	if (hsync)
		dcfg |= VP_DCFG_HSYNC_EN;
	if (vsync)
		dcfg |= VP_DCFG_VSYNC_EN;
	if (crt)
		dcfg |= VP_DCFG_CRT_EN;
	write_vp(par, VP_DCFG, dcfg);

	/* Power on/off flat panel. */

	if (par->enable_crt == 0) {
		fp_pm = read_fp(par, FP_PM);
		if (blank_mode == FB_BLANK_POWERDOWN)
			fp_pm &= ~FP_PM_P;
		else
			fp_pm |= FP_PM_P;
		write_fp(par, FP_PM, fp_pm);
	}

	return 0;
}