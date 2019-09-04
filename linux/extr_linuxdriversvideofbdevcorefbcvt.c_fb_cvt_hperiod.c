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
struct fb_cvt_data {int f_refresh; int flags; int yres; int interlace; int v_margin; } ;

/* Variables and functions */
 int FB_CVT_FLAG_REDUCED_BLANK ; 
 int FB_CVT_MIN_VPORCH ; 
 int FB_CVT_MIN_VSYNC_BP ; 
 int FB_CVT_RB_MIN_VBLANK ; 

__attribute__((used)) static u32 fb_cvt_hperiod(struct fb_cvt_data *cvt)
{
	u32 num = 1000000000/cvt->f_refresh;
	u32 den;

	if (cvt->flags & FB_CVT_FLAG_REDUCED_BLANK) {
		num -= FB_CVT_RB_MIN_VBLANK * 1000;
		den = 2 * (cvt->yres/cvt->interlace + 2 * cvt->v_margin);
	} else {
		num -= FB_CVT_MIN_VSYNC_BP * 1000;
		den = 2 * (cvt->yres/cvt->interlace + cvt->v_margin * 2
			   + FB_CVT_MIN_VPORCH + cvt->interlace/2);
	}

	return 2 * (num/den);
}