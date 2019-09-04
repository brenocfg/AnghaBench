#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  void* u16 ;
struct omapfb_info {int num_overlays; int* rotation; scalar_t__ rotation_type; int mirror; TYPE_1__* region; int /*<<< orphan*/  id; struct omap_overlay** overlays; } ;
struct omap_overlay_info {int screen_width; int width; int height; int color_mode; scalar_t__ rotation_type; int rotation; int mirror; void* out_height; void* out_width; void* pos_y; void* pos_x; int /*<<< orphan*/  paddr; } ;
struct omap_overlay {int (* set_overlay_info ) (struct omap_overlay*,struct omap_overlay_info*) ;int /*<<< orphan*/  (* get_overlay_info ) (struct omap_overlay*,struct omap_overlay_info*) ;} ;
struct fb_var_screeninfo {int rotate; int yres; int xres; int nonstd; int bits_per_pixel; } ;
struct fb_fix_screeninfo {int line_length; } ;
struct fb_info {struct fb_fix_screeninfo fix; struct fb_var_screeninfo var; } ;
typedef  enum omap_color_mode { ____Placeholder_omap_color_mode } omap_color_mode ;
struct TYPE_2__ {scalar_t__ size; int /*<<< orphan*/  lock_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,...) ; 
 struct omapfb_info* FB2OFB (struct fb_info*) ; 
 int FB_ROTATE_CCW ; 
 int FB_ROTATE_CW ; 
#define  OMAPFB_COLOR_YUV422 129 
#define  OMAPFB_COLOR_YUY422 128 
 scalar_t__ OMAP_DSS_ROT_VRFB ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int fb_mode_to_dss_mode (struct fb_var_screeninfo*,int*) ; 
 int /*<<< orphan*/  omapfb_calc_addr (struct omapfb_info*,struct fb_var_screeninfo*,struct fb_fix_screeninfo*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct omap_overlay*,struct omap_overlay_info*) ; 
 int stub2 (struct omap_overlay*,struct omap_overlay_info*) ; 

int omapfb_setup_overlay(struct fb_info *fbi, struct omap_overlay *ovl,
		u16 posx, u16 posy, u16 outw, u16 outh)
{
	int r = 0;
	struct omapfb_info *ofbi = FB2OFB(fbi);
	struct fb_var_screeninfo *var = &fbi->var;
	struct fb_fix_screeninfo *fix = &fbi->fix;
	enum omap_color_mode mode = 0;
	u32 data_start_p = 0;
	struct omap_overlay_info info;
	int xres, yres;
	int screen_width;
	int mirror;
	int rotation = var->rotate;
	int i;

	WARN_ON(!atomic_read(&ofbi->region->lock_count));

	for (i = 0; i < ofbi->num_overlays; i++) {
		if (ovl != ofbi->overlays[i])
			continue;

		rotation = (rotation + ofbi->rotation[i]) % 4;
		break;
	}

	DBG("setup_overlay %d, posx %d, posy %d, outw %d, outh %d\n", ofbi->id,
			posx, posy, outw, outh);

	if (rotation == FB_ROTATE_CW || rotation == FB_ROTATE_CCW) {
		xres = var->yres;
		yres = var->xres;
	} else {
		xres = var->xres;
		yres = var->yres;
	}

	if (ofbi->region->size)
		omapfb_calc_addr(ofbi, var, fix, rotation, &data_start_p);

	r = fb_mode_to_dss_mode(var, &mode);
	if (r) {
		DBG("fb_mode_to_dss_mode failed");
		goto err;
	}

	switch (var->nonstd) {
	case OMAPFB_COLOR_YUV422:
	case OMAPFB_COLOR_YUY422:
		if (ofbi->rotation_type == OMAP_DSS_ROT_VRFB) {
			screen_width = fix->line_length
				/ (var->bits_per_pixel >> 2);
			break;
		}
		/* fall through */
	default:
		screen_width = fix->line_length / (var->bits_per_pixel >> 3);
		break;
	}

	ovl->get_overlay_info(ovl, &info);

	if (ofbi->rotation_type == OMAP_DSS_ROT_VRFB)
		mirror = 0;
	else
		mirror = ofbi->mirror;

	info.paddr = data_start_p;
	info.screen_width = screen_width;
	info.width = xres;
	info.height = yres;
	info.color_mode = mode;
	info.rotation_type = ofbi->rotation_type;
	info.rotation = rotation;
	info.mirror = mirror;

	info.pos_x = posx;
	info.pos_y = posy;
	info.out_width = outw;
	info.out_height = outh;

	r = ovl->set_overlay_info(ovl, &info);
	if (r) {
		DBG("ovl->setup_overlay_info failed\n");
		goto err;
	}

	return 0;

err:
	DBG("setup_overlay failed\n");
	return r;
}