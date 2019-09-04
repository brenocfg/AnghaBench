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
struct nuc900fb_hw {int lcd_crtc_size; int lcd_crtc_dend; int lcd_crtc_hr; int lcd_crtc_hsync; int lcd_crtc_vr; } ;
struct fb_var_screeninfo {int height; int upper_margin; int lower_margin; int width; int left_margin; int right_margin; scalar_t__ vsync_len; scalar_t__ hsync_len; } ;
struct fb_info {struct fb_var_screeninfo var; } ;

/* Variables and functions */
 int LCM_CRTC_DEND_HDENDVAL (int) ; 
 int LCM_CRTC_DEND_VDENDVAL (int) ; 
 int LCM_CRTC_HR_EVAL (int) ; 
 int LCM_CRTC_HR_SVAL (int) ; 
 int LCM_CRTC_HSYNC_EVAL (scalar_t__) ; 
 int LCM_CRTC_HSYNC_SVAL (int) ; 
 int LCM_CRTC_SIZE_HTTVAL (int) ; 
 int LCM_CRTC_SIZE_VTTVAL (int) ; 
 int LCM_CRTC_VR_EVAL (scalar_t__) ; 
 int LCM_CRTC_VR_SVAL (int) ; 

__attribute__((used)) static void nuc900fb_calculate_lcd_regs(const struct fb_info *info,
					struct nuc900fb_hw *regs)
{
	const struct fb_var_screeninfo *var = &info->var;
	int vtt = var->height + var->upper_margin + var->lower_margin;
	int htt = var->width + var->left_margin + var->right_margin;
	int hsync = var->width + var->right_margin;
	int vsync = var->height + var->lower_margin;

	regs->lcd_crtc_size = LCM_CRTC_SIZE_VTTVAL(vtt) |
			      LCM_CRTC_SIZE_HTTVAL(htt);
	regs->lcd_crtc_dend = LCM_CRTC_DEND_VDENDVAL(var->height) |
			      LCM_CRTC_DEND_HDENDVAL(var->width);
	regs->lcd_crtc_hr = LCM_CRTC_HR_EVAL(var->width + 5) |
			    LCM_CRTC_HR_SVAL(var->width + 1);
	regs->lcd_crtc_hsync = LCM_CRTC_HSYNC_EVAL(hsync + var->hsync_len) |
			       LCM_CRTC_HSYNC_SVAL(hsync);
	regs->lcd_crtc_vr = LCM_CRTC_VR_EVAL(vsync + var->vsync_len) |
			    LCM_CRTC_VR_SVAL(vsync);

}