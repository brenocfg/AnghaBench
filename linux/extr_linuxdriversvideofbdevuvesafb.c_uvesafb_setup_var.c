#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct vbe_mode_ib {int y_res; int bytes_per_scan_line; int bits_per_pixel; int red_len; int green_len; int blue_len; scalar_t__ rsvd_len; scalar_t__ rsvd_off; scalar_t__ blue_off; scalar_t__ green_off; scalar_t__ red_off; int /*<<< orphan*/  x_res; } ;
struct uvesafb_par {scalar_t__ ypan; } ;
struct TYPE_10__ {scalar_t__ length; scalar_t__ offset; } ;
struct TYPE_9__ {int length; scalar_t__ offset; } ;
struct TYPE_8__ {int length; scalar_t__ offset; } ;
struct TYPE_7__ {int length; scalar_t__ offset; } ;
struct fb_var_screeninfo {int yres; int yres_virtual; int bits_per_pixel; TYPE_5__ transp; TYPE_4__ blue; TYPE_3__ green; TYPE_2__ red; scalar_t__ yoffset; scalar_t__ xoffset; int /*<<< orphan*/  xres_virtual; int /*<<< orphan*/  xres; int /*<<< orphan*/  sync; int /*<<< orphan*/  vmode; } ;
struct TYPE_6__ {int smem_len; } ;
struct fb_info {TYPE_1__ fix; struct uvesafb_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB_SYNC_VERT_HIGH_ACT ; 
 int /*<<< orphan*/  FB_VMODE_NONINTERLACED ; 

__attribute__((used)) static void uvesafb_setup_var(struct fb_var_screeninfo *var,
		struct fb_info *info, struct vbe_mode_ib *mode)
{
	struct uvesafb_par *par = info->par;

	var->vmode = FB_VMODE_NONINTERLACED;
	var->sync = FB_SYNC_VERT_HIGH_ACT;

	var->xres = mode->x_res;
	var->yres = mode->y_res;
	var->xres_virtual = mode->x_res;
	var->yres_virtual = (par->ypan) ?
			info->fix.smem_len / mode->bytes_per_scan_line :
			mode->y_res;
	var->xoffset = 0;
	var->yoffset = 0;
	var->bits_per_pixel = mode->bits_per_pixel;

	if (var->bits_per_pixel == 15)
		var->bits_per_pixel = 16;

	if (var->bits_per_pixel > 8) {
		var->red.offset    = mode->red_off;
		var->red.length    = mode->red_len;
		var->green.offset  = mode->green_off;
		var->green.length  = mode->green_len;
		var->blue.offset   = mode->blue_off;
		var->blue.length   = mode->blue_len;
		var->transp.offset = mode->rsvd_off;
		var->transp.length = mode->rsvd_len;
	} else {
		var->red.offset    = 0;
		var->green.offset  = 0;
		var->blue.offset   = 0;
		var->transp.offset = 0;

		var->red.length    = 8;
		var->green.length  = 8;
		var->blue.length   = 8;
		var->transp.length = 0;
	}
}