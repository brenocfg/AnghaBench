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
struct mfb_info {int y_aoi_d; int x_aoi_d; struct diu_ad* ad; } ;
struct fb_var_screeninfo {int yoffset; int xoffset; } ;
struct fb_info {struct mfb_info* par; struct fb_var_screeninfo var; } ;
struct diu_ad {void* offset_xyd; void* offset_xyi; } ;

/* Variables and functions */
 void* cpu_to_le32 (int) ; 

__attribute__((used)) static int fsl_diu_set_aoi(struct fb_info *info)
{
	struct fb_var_screeninfo *var = &info->var;
	struct mfb_info *mfbi = info->par;
	struct diu_ad *ad = mfbi->ad;

	/* AOI should not be greater than display size */
	ad->offset_xyi = cpu_to_le32((var->yoffset << 16) | var->xoffset);
	ad->offset_xyd = cpu_to_le32((mfbi->y_aoi_d << 16) | mfbi->x_aoi_d);
	return 0;
}