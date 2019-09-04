#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int height; int width; scalar_t__ accel_flags; scalar_t__ nonstd; int /*<<< orphan*/  activate; int /*<<< orphan*/  vmode; int /*<<< orphan*/  bits_per_pixel; void* yres_virtual; void* xres_virtual; void* yres; void* xres; } ;
struct TYPE_9__ {int hfmax; int vfmax; int dclkmin; int dclkmax; scalar_t__ vfmin; scalar_t__ hfmin; } ;
struct TYPE_8__ {int xpanstep; int ypanstep; int /*<<< orphan*/  accel; scalar_t__ ywrapstep; scalar_t__ type_aux; int /*<<< orphan*/  type; int /*<<< orphan*/  id; } ;
struct TYPE_10__ {int flags; TYPE_5__ var; TYPE_2__ monspecs; TYPE_1__ fix; int /*<<< orphan*/  pseudo_palette; int /*<<< orphan*/ * fbops; } ;
struct bcm2708_fb {TYPE_3__ fb; int /*<<< orphan*/  dma_waitq; int /*<<< orphan*/  cmap; } ;

/* Variables and functions */
 int FBINFO_FLAG_DEFAULT ; 
 int FBINFO_HWACCEL_COPYAREA ; 
 int /*<<< orphan*/  FB_ACCEL_NONE ; 
 int /*<<< orphan*/  FB_ACTIVATE_NOW ; 
 int /*<<< orphan*/  FB_TYPE_PACKED_PIXELS ; 
 int /*<<< orphan*/  FB_VMODE_NONINTERLACED ; 
 int /*<<< orphan*/  bcm2708_fb_ops ; 
 int /*<<< orphan*/  bcm2708_fb_set_bitfields (TYPE_5__*) ; 
 int bcm2708_fb_set_par (TYPE_3__*) ; 
 int /*<<< orphan*/  bcm2708_name ; 
 int /*<<< orphan*/  fb_set_var (TYPE_3__*,TYPE_5__*) ; 
 int /*<<< orphan*/  fbdepth ; 
 void* fbheight ; 
 int /*<<< orphan*/  fbswap ; 
 void* fbwidth ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_debug (char*,int,...) ; 
 int register_framebuffer (TYPE_3__*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bcm2708_fb_register(struct bcm2708_fb *fb)
{
	int ret;

	fb->fb.fbops = &bcm2708_fb_ops;
	fb->fb.flags = FBINFO_FLAG_DEFAULT | FBINFO_HWACCEL_COPYAREA;
	fb->fb.pseudo_palette = fb->cmap;

	strncpy(fb->fb.fix.id, bcm2708_name, sizeof(fb->fb.fix.id));
	fb->fb.fix.type = FB_TYPE_PACKED_PIXELS;
	fb->fb.fix.type_aux = 0;
	fb->fb.fix.xpanstep = 1;
	fb->fb.fix.ypanstep = 1;
	fb->fb.fix.ywrapstep = 0;
	fb->fb.fix.accel = FB_ACCEL_NONE;

	fb->fb.var.xres = fbwidth;
	fb->fb.var.yres = fbheight;
	fb->fb.var.xres_virtual = fbwidth;
	fb->fb.var.yres_virtual = fbheight;
	fb->fb.var.bits_per_pixel = fbdepth;
	fb->fb.var.vmode = FB_VMODE_NONINTERLACED;
	fb->fb.var.activate = FB_ACTIVATE_NOW;
	fb->fb.var.nonstd = 0;
	fb->fb.var.height = -1;		/* height of picture in mm    */
	fb->fb.var.width = -1;		/* width of picture in mm    */
	fb->fb.var.accel_flags = 0;

	fb->fb.monspecs.hfmin = 0;
	fb->fb.monspecs.hfmax = 100000;
	fb->fb.monspecs.vfmin = 0;
	fb->fb.monspecs.vfmax = 400;
	fb->fb.monspecs.dclkmin = 1000000;
	fb->fb.monspecs.dclkmax = 100000000;

	bcm2708_fb_set_bitfields(&fb->fb.var);
	init_waitqueue_head(&fb->dma_waitq);

	/*
	 * Allocate colourmap.
	 */

	fb_set_var(&fb->fb, &fb->fb.var);
	ret = bcm2708_fb_set_par(&fb->fb);
	if (ret)
		return ret;

	print_debug("BCM2708FB: registering framebuffer (%dx%d@%d) (%d)\n",
		    fbwidth, fbheight, fbdepth, fbswap);

	ret = register_framebuffer(&fb->fb);
	print_debug("BCM2708FB: register framebuffer (%d)\n", ret);
	if (ret == 0)
		goto out;

	print_debug("BCM2708FB: cannot register framebuffer (%d)\n", ret);
out:
	return ret;
}