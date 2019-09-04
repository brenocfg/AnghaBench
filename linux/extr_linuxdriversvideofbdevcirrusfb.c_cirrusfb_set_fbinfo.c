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
struct fb_var_screeninfo {int bits_per_pixel; } ;
struct TYPE_3__ {int smem_len; int xpanstep; int ypanstep; scalar_t__ mmio_len; scalar_t__ ywrapstep; scalar_t__ type_aux; int /*<<< orphan*/  id; int /*<<< orphan*/  accel; } ;
struct fb_info {int flags; int screen_base; int screen_size; int /*<<< orphan*/  cmap; TYPE_1__ fix; int /*<<< orphan*/ * fbops; int /*<<< orphan*/  pseudo_palette; struct fb_var_screeninfo var; struct cirrusfb_info* par; } ;
struct cirrusfb_info {size_t btype; int /*<<< orphan*/  pseudo_palette; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 size_t BT_GD5480 ; 
 int FBINFO_DEFAULT ; 
 int FBINFO_HWACCEL_COPYAREA ; 
 int FBINFO_HWACCEL_DISABLED ; 
 int FBINFO_HWACCEL_FILLRECT ; 
 int FBINFO_HWACCEL_IMAGEBLIT ; 
 int FBINFO_HWACCEL_XPAN ; 
 int FBINFO_HWACCEL_YPAN ; 
 int /*<<< orphan*/  FB_ACCEL_CIRRUS_ALPINE ; 
 int /*<<< orphan*/  FB_ACCEL_NONE ; 
 int MB_ ; 
 TYPE_2__* cirrusfb_board_info ; 
 int /*<<< orphan*/  cirrusfb_ops ; 
 int /*<<< orphan*/  fb_alloc_cmap (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ is_laguna (struct cirrusfb_info*) ; 
 scalar_t__ noaccel ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cirrusfb_set_fbinfo(struct fb_info *info)
{
	struct cirrusfb_info *cinfo = info->par;
	struct fb_var_screeninfo *var = &info->var;

	info->pseudo_palette = cinfo->pseudo_palette;
	info->flags = FBINFO_DEFAULT
		    | FBINFO_HWACCEL_XPAN
		    | FBINFO_HWACCEL_YPAN
		    | FBINFO_HWACCEL_FILLRECT
		    | FBINFO_HWACCEL_IMAGEBLIT
		    | FBINFO_HWACCEL_COPYAREA;
	if (noaccel || is_laguna(cinfo)) {
		info->flags |= FBINFO_HWACCEL_DISABLED;
		info->fix.accel = FB_ACCEL_NONE;
	} else
		info->fix.accel = FB_ACCEL_CIRRUS_ALPINE;

	info->fbops = &cirrusfb_ops;

	if (cinfo->btype == BT_GD5480) {
		if (var->bits_per_pixel == 16)
			info->screen_base += 1 * MB_;
		if (var->bits_per_pixel == 32)
			info->screen_base += 2 * MB_;
	}

	/* Fill fix common fields */
	strlcpy(info->fix.id, cirrusfb_board_info[cinfo->btype].name,
		sizeof(info->fix.id));

	/* monochrome: only 1 memory plane */
	/* 8 bit and above: Use whole memory area */
	info->fix.smem_len   = info->screen_size;
	if (var->bits_per_pixel == 1)
		info->fix.smem_len /= 4;
	info->fix.type_aux   = 0;
	info->fix.xpanstep   = 1;
	info->fix.ypanstep   = 1;
	info->fix.ywrapstep  = 0;

	/* FIXME: map region at 0xB8000 if available, fill in here */
	info->fix.mmio_len   = 0;

	fb_alloc_cmap(&info->cmap, 256, 0);

	return 0;
}