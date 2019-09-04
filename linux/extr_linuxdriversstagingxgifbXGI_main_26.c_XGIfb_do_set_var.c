#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xgi_hw_device_info {int dummy; } ;
struct vb_device_info {int /*<<< orphan*/  P3c4; int /*<<< orphan*/  P3d4; } ;
struct xgifb_video_info {unsigned int refresh_rate; int mode_idx; int rate_idx; scalar_t__ video_bpp; int video_vwidth; unsigned int video_width; scalar_t__ video_height; int video_linelength; int DstColor; int XGI310_AccelDepth; int video_cmap_len; scalar_t__ org_y; scalar_t__ org_x; int /*<<< orphan*/  video_vheight; struct xgi_hw_device_info hw_info; struct vb_device_info dev_info; } ;
struct fb_var_screeninfo {unsigned int xres; unsigned int right_margin; unsigned int hsync_len; unsigned int yres; unsigned int lower_margin; unsigned int vsync_len; int xres_virtual; scalar_t__ bits_per_pixel; int vmode; int pixclock; int /*<<< orphan*/  yres_virtual; int /*<<< orphan*/  upper_margin; int /*<<< orphan*/  left_margin; } ;
struct TYPE_5__ {int xres_virtual; scalar_t__ bits_per_pixel; int /*<<< orphan*/  yres_virtual; } ;
struct TYPE_4__ {int line_length; } ;
struct fb_info {TYPE_2__ var; TYPE_1__ fix; struct xgifb_video_info* par; } ;
struct TYPE_6__ {scalar_t__ mode_no; unsigned int xres; scalar_t__ yres; scalar_t__ bpp; } ;

/* Variables and functions */
 int EINVAL ; 
 int FB_VMODE_DOUBLE ; 
 int FB_VMODE_MASK ; 
 int FB_VMODE_NONINTERLACED ; 
 int IND_SIS_PASSWORD ; 
 int SIS_PASSWORD ; 
 scalar_t__ XGISetModeNew (struct xgifb_video_info*,struct xgi_hw_device_info*,scalar_t__) ; 
 TYPE_3__* XGIbios_mode ; 
 int /*<<< orphan*/  XGIfb_bpp_to_var (struct xgifb_video_info*,struct fb_var_screeninfo*) ; 
 int /*<<< orphan*/  XGIfb_post_setmode (struct xgifb_video_info*) ; 
 int /*<<< orphan*/  XGIfb_pre_setmode (struct xgifb_video_info*) ; 
 scalar_t__ XGIfb_search_refresh_rate (struct xgifb_video_info*,int) ; 
 size_t XGIfb_validate_mode (struct xgifb_video_info*,size_t) ; 
 int /*<<< orphan*/  dumpVGAReg (struct xgifb_video_info*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int XGIfb_do_set_var(struct fb_var_screeninfo *var, int isactive,
			    struct fb_info *info)
{
	struct xgifb_video_info *xgifb_info = info->par;
	struct vb_device_info *vb = &xgifb_info->dev_info;
	struct xgi_hw_device_info *hw_info = &xgifb_info->hw_info;
	unsigned int htotal = var->left_margin + var->xres + var->right_margin
			+ var->hsync_len;
	unsigned int vtotal = var->upper_margin + var->yres + var->lower_margin
			+ var->vsync_len;
#if defined(__BIG_ENDIAN)
	u8 cr_data;
#endif
	unsigned int drate = 0, hrate = 0;
	int found_mode = 0;
	int old_mode;

	info->var.xres_virtual = var->xres_virtual;
	info->var.yres_virtual = var->yres_virtual;
	info->var.bits_per_pixel = var->bits_per_pixel;

	if ((var->vmode & FB_VMODE_MASK) == FB_VMODE_NONINTERLACED)
		vtotal <<= 1;
	else if ((var->vmode & FB_VMODE_MASK) == FB_VMODE_DOUBLE)
		vtotal <<= 2;

	if (!htotal || !vtotal) {
		pr_debug("Invalid 'var' information\n");
		return -EINVAL;
	} pr_debug("var->pixclock=%d, htotal=%d, vtotal=%d\n",
			var->pixclock, htotal, vtotal);

	if (var->pixclock) {
		drate = 1000000000 / var->pixclock;
		hrate = (drate * 1000) / htotal;
		xgifb_info->refresh_rate = (unsigned int)(hrate * 2
				/ vtotal);
	} else {
		xgifb_info->refresh_rate = 60;
	}

	pr_debug("Change mode to %dx%dx%d-%dHz\n",
		 var->xres, var->yres, var->bits_per_pixel,
		 xgifb_info->refresh_rate);

	old_mode = xgifb_info->mode_idx;
	xgifb_info->mode_idx = 0;

	while ((XGIbios_mode[xgifb_info->mode_idx].mode_no != 0) &&
	       (XGIbios_mode[xgifb_info->mode_idx].xres <= var->xres)) {
		if ((XGIbios_mode[xgifb_info->mode_idx].xres == var->xres) &&
		    (XGIbios_mode[xgifb_info->mode_idx].yres == var->yres) &&
		    (XGIbios_mode[xgifb_info->mode_idx].bpp
						== var->bits_per_pixel)) {
			found_mode = 1;
			break;
		}
		xgifb_info->mode_idx++;
	}

	if (found_mode)
		xgifb_info->mode_idx = XGIfb_validate_mode(xgifb_info,
							xgifb_info->mode_idx);
	else
		xgifb_info->mode_idx = -1;

	if (xgifb_info->mode_idx < 0) {
		pr_err("Mode %dx%dx%d not supported\n",
		       var->xres, var->yres, var->bits_per_pixel);
		xgifb_info->mode_idx = old_mode;
		return -EINVAL;
	}

	if (XGIfb_search_refresh_rate(xgifb_info,
				      xgifb_info->refresh_rate) == 0) {
		xgifb_info->rate_idx = 1;
		xgifb_info->refresh_rate = 60;
	}

	if (isactive) {
		XGIfb_pre_setmode(xgifb_info);
		if (XGISetModeNew(xgifb_info, hw_info,
				  XGIbios_mode[xgifb_info->mode_idx].mode_no)
					== 0) {
			pr_err("Setting mode[0x%x] failed\n",
			       XGIbios_mode[xgifb_info->mode_idx].mode_no);
			return -EINVAL;
		}
		info->fix.line_length = (info->var.xres_virtual
				* info->var.bits_per_pixel) >> 6;

		xgifb_reg_set(vb->P3c4, IND_SIS_PASSWORD, SIS_PASSWORD);

		xgifb_reg_set(vb->P3d4, 0x13, (info->fix.line_length & 0x00ff));
		xgifb_reg_set(vb->P3c4, 0x0E,
			      (info->fix.line_length & 0xff00) >> 8);

		XGIfb_post_setmode(xgifb_info);

		pr_debug("Set new mode: %dx%dx%d-%d\n",
			 XGIbios_mode[xgifb_info->mode_idx].xres,
			 XGIbios_mode[xgifb_info->mode_idx].yres,
			 XGIbios_mode[xgifb_info->mode_idx].bpp,
			 xgifb_info->refresh_rate);

		xgifb_info->video_bpp = XGIbios_mode[xgifb_info->mode_idx].bpp;
		xgifb_info->video_vwidth = info->var.xres_virtual;
		xgifb_info->video_width =
			XGIbios_mode[xgifb_info->mode_idx].xres;
		xgifb_info->video_vheight = info->var.yres_virtual;
		xgifb_info->video_height =
			XGIbios_mode[xgifb_info->mode_idx].yres;
		xgifb_info->org_x = 0;
		xgifb_info->org_y = 0;
		xgifb_info->video_linelength = info->var.xres_virtual
				* (xgifb_info->video_bpp >> 3);
		switch (xgifb_info->video_bpp) {
		case 8:
			xgifb_info->DstColor = 0x0000;
			xgifb_info->XGI310_AccelDepth = 0x00000000;
			xgifb_info->video_cmap_len = 256;
#if defined(__BIG_ENDIAN)
			cr_data = xgifb_reg_get(vb->P3d4, 0x4D);
			xgifb_reg_set(vb->P3d4, 0x4D, (cr_data & 0xE0));
#endif
			break;
		case 16:
			xgifb_info->DstColor = 0x8000;
			xgifb_info->XGI310_AccelDepth = 0x00010000;
#if defined(__BIG_ENDIAN)
			cr_data = xgifb_reg_get(vb->P3d4, 0x4D);
			xgifb_reg_set(vb->P3d4, 0x4D, ((cr_data & 0xE0) | 0x0B));
#endif
			xgifb_info->video_cmap_len = 16;
			break;
		case 32:
			xgifb_info->DstColor = 0xC000;
			xgifb_info->XGI310_AccelDepth = 0x00020000;
			xgifb_info->video_cmap_len = 16;
#if defined(__BIG_ENDIAN)
			cr_data = xgifb_reg_get(vb->P3d4, 0x4D);
			xgifb_reg_set(vb->P3d4, 0x4D, ((cr_data & 0xE0) | 0x15));
#endif
			break;
		default:
			xgifb_info->video_cmap_len = 16;
			pr_err("Unsupported depth %d\n",
			       xgifb_info->video_bpp);
			break;
		}
	}
	XGIfb_bpp_to_var(xgifb_info, var); /* update ARGB info */

	dumpVGAReg(xgifb_info);
	return 0;
}