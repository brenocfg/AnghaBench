#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mfb_info {int index; scalar_t__ x_aoi_d; scalar_t__ y_aoi_d; int /*<<< orphan*/  count; struct fsl_diu_data* parent; } ;
struct fsl_diu_data {TYPE_2__* fsl_diu_info; } ;
struct fb_var_screeninfo {void* xres; int yres; } ;
struct fb_info {struct mfb_info* par; } ;
typedef  enum mfb_index { ____Placeholder_mfb_index } mfb_index ;
typedef  void* __u32 ;
struct TYPE_3__ {void* yres; void* xres; } ;
struct TYPE_4__ {TYPE_1__ var; struct mfb_info* par; } ;

/* Variables and functions */
#define  PLANE0 132 
#define  PLANE1_AOI0 131 
#define  PLANE1_AOI1 130 
#define  PLANE2_AOI0 129 
#define  PLANE2_AOI1 128 

__attribute__((used)) static void adjust_aoi_size_position(struct fb_var_screeninfo *var,
				struct fb_info *info)
{
	struct mfb_info *lower_aoi_mfbi, *upper_aoi_mfbi, *mfbi = info->par;
	struct fsl_diu_data *data = mfbi->parent;
	int available_height, upper_aoi_bottom;
	enum mfb_index index = mfbi->index;
	int lower_aoi_is_open, upper_aoi_is_open;
	__u32 base_plane_width, base_plane_height, upper_aoi_height;

	base_plane_width = data->fsl_diu_info[0].var.xres;
	base_plane_height = data->fsl_diu_info[0].var.yres;

	if (mfbi->x_aoi_d < 0)
		mfbi->x_aoi_d = 0;
	if (mfbi->y_aoi_d < 0)
		mfbi->y_aoi_d = 0;
	switch (index) {
	case PLANE0:
		if (mfbi->x_aoi_d != 0)
			mfbi->x_aoi_d = 0;
		if (mfbi->y_aoi_d != 0)
			mfbi->y_aoi_d = 0;
		break;
	case PLANE1_AOI0:
	case PLANE2_AOI0:
		lower_aoi_mfbi = data->fsl_diu_info[index+1].par;
		lower_aoi_is_open = lower_aoi_mfbi->count > 0 ? 1 : 0;
		if (var->xres > base_plane_width)
			var->xres = base_plane_width;
		if ((mfbi->x_aoi_d + var->xres) > base_plane_width)
			mfbi->x_aoi_d = base_plane_width - var->xres;

		if (lower_aoi_is_open)
			available_height = lower_aoi_mfbi->y_aoi_d;
		else
			available_height = base_plane_height;
		if (var->yres > available_height)
			var->yres = available_height;
		if ((mfbi->y_aoi_d + var->yres) > available_height)
			mfbi->y_aoi_d = available_height - var->yres;
		break;
	case PLANE1_AOI1:
	case PLANE2_AOI1:
		upper_aoi_mfbi = data->fsl_diu_info[index-1].par;
		upper_aoi_height = data->fsl_diu_info[index-1].var.yres;
		upper_aoi_bottom = upper_aoi_mfbi->y_aoi_d + upper_aoi_height;
		upper_aoi_is_open = upper_aoi_mfbi->count > 0 ? 1 : 0;
		if (var->xres > base_plane_width)
			var->xres = base_plane_width;
		if ((mfbi->x_aoi_d + var->xres) > base_plane_width)
			mfbi->x_aoi_d = base_plane_width - var->xres;
		if (mfbi->y_aoi_d < 0)
			mfbi->y_aoi_d = 0;
		if (upper_aoi_is_open) {
			if (mfbi->y_aoi_d < upper_aoi_bottom)
				mfbi->y_aoi_d = upper_aoi_bottom;
			available_height = base_plane_height
						- upper_aoi_bottom;
		} else
			available_height = base_plane_height;
		if (var->yres > available_height)
			var->yres = available_height;
		if ((mfbi->y_aoi_d + var->yres) > base_plane_height)
			mfbi->y_aoi_d = base_plane_height - var->yres;
		break;
	}
}