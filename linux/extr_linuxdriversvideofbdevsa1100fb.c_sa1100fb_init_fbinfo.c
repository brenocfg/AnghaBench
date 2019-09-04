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
typedef  scalar_t__ u_char ;
struct sa1100fb_mach_info {int lccr3; scalar_t__ pixclock; int xres; int yres; int bpp; int /*<<< orphan*/ ** rgb; int /*<<< orphan*/  cmap_greyscale; int /*<<< orphan*/  sync; int /*<<< orphan*/  lower_margin; int /*<<< orphan*/  upper_margin; int /*<<< orphan*/  vsync_len; int /*<<< orphan*/  right_margin; int /*<<< orphan*/  left_margin; int /*<<< orphan*/  hsync_len; } ;
struct TYPE_5__ {int smem_len; int /*<<< orphan*/  accel; scalar_t__ ywrapstep; scalar_t__ ypanstep; scalar_t__ xpanstep; scalar_t__ type_aux; int /*<<< orphan*/  type; int /*<<< orphan*/  id; } ;
struct TYPE_4__ {int height; int width; int xres; int xres_virtual; int yres; int yres_virtual; int bits_per_pixel; scalar_t__ pixclock; int /*<<< orphan*/  grayscale; int /*<<< orphan*/  sync; int /*<<< orphan*/  lower_margin; int /*<<< orphan*/  upper_margin; int /*<<< orphan*/  vsync_len; int /*<<< orphan*/  right_margin; int /*<<< orphan*/  left_margin; int /*<<< orphan*/  hsync_len; int /*<<< orphan*/  vmode; scalar_t__ accel_flags; int /*<<< orphan*/  activate; scalar_t__ nonstd; } ;
struct TYPE_6__ {TYPE_2__ fix; TYPE_1__ var; int /*<<< orphan*/  pseudo_palette; int /*<<< orphan*/  monspecs; int /*<<< orphan*/  flags; int /*<<< orphan*/ * fbops; } ;
struct sa1100fb_info {int /*<<< orphan*/  ctrlr_lock; int /*<<< orphan*/  task; int /*<<< orphan*/  ctrlr_wait; int /*<<< orphan*/ ** rgb; struct sa1100fb_mach_info* inf; TYPE_3__ fb; scalar_t__ task_state; int /*<<< orphan*/  state; int /*<<< orphan*/  pseudo_palette; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  C_STARTUP ; 
 int /*<<< orphan*/  FBINFO_DEFAULT ; 
 int /*<<< orphan*/  FB_ACCEL_NONE ; 
 int /*<<< orphan*/  FB_ACTIVATE_NOW ; 
 int /*<<< orphan*/  FB_TYPE_PACKED_PIXELS ; 
 int /*<<< orphan*/  FB_VMODE_NONINTERLACED ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int LCCR3_HorSnchL ; 
 int LCCR3_VrtSnchL ; 
 unsigned int NR_RGB ; 
 size_t RGB_16 ; 
 size_t RGB_4 ; 
 size_t RGB_8 ; 
 int /*<<< orphan*/  SA1100_NAME ; 
 int /*<<< orphan*/  def_rgb_16 ; 
 struct sa1100fb_mach_info* dev_get_platdata (struct device*) ; 
 struct sa1100fb_info* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  monspecs ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  rgb_4 ; 
 int /*<<< orphan*/  rgb_8 ; 
 int /*<<< orphan*/  sa1100fb_ops ; 
 int /*<<< orphan*/  sa1100fb_task ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sa1100fb_info *sa1100fb_init_fbinfo(struct device *dev)
{
	struct sa1100fb_mach_info *inf = dev_get_platdata(dev);
	struct sa1100fb_info *fbi;
	unsigned i;

	fbi = devm_kzalloc(dev, sizeof(struct sa1100fb_info), GFP_KERNEL);
	if (!fbi)
		return NULL;

	fbi->dev = dev;

	strcpy(fbi->fb.fix.id, SA1100_NAME);

	fbi->fb.fix.type	= FB_TYPE_PACKED_PIXELS;
	fbi->fb.fix.type_aux	= 0;
	fbi->fb.fix.xpanstep	= 0;
	fbi->fb.fix.ypanstep	= 0;
	fbi->fb.fix.ywrapstep	= 0;
	fbi->fb.fix.accel	= FB_ACCEL_NONE;

	fbi->fb.var.nonstd	= 0;
	fbi->fb.var.activate	= FB_ACTIVATE_NOW;
	fbi->fb.var.height	= -1;
	fbi->fb.var.width	= -1;
	fbi->fb.var.accel_flags	= 0;
	fbi->fb.var.vmode	= FB_VMODE_NONINTERLACED;

	fbi->fb.fbops		= &sa1100fb_ops;
	fbi->fb.flags		= FBINFO_DEFAULT;
	fbi->fb.monspecs	= monspecs;
	fbi->fb.pseudo_palette	= fbi->pseudo_palette;

	fbi->rgb[RGB_4]		= &rgb_4;
	fbi->rgb[RGB_8]		= &rgb_8;
	fbi->rgb[RGB_16]	= &def_rgb_16;

	/*
	 * People just don't seem to get this.  We don't support
	 * anything but correct entries now, so panic if someone
	 * does something stupid.
	 */
	if (inf->lccr3 & (LCCR3_VrtSnchL|LCCR3_HorSnchL|0xff) ||
	    inf->pixclock == 0)
		panic("sa1100fb error: invalid LCCR3 fields set or zero "
			"pixclock.");

	fbi->fb.var.xres		= inf->xres;
	fbi->fb.var.xres_virtual	= inf->xres;
	fbi->fb.var.yres		= inf->yres;
	fbi->fb.var.yres_virtual	= inf->yres;
	fbi->fb.var.bits_per_pixel	= inf->bpp;
	fbi->fb.var.pixclock		= inf->pixclock;
	fbi->fb.var.hsync_len		= inf->hsync_len;
	fbi->fb.var.left_margin		= inf->left_margin;
	fbi->fb.var.right_margin	= inf->right_margin;
	fbi->fb.var.vsync_len		= inf->vsync_len;
	fbi->fb.var.upper_margin	= inf->upper_margin;
	fbi->fb.var.lower_margin	= inf->lower_margin;
	fbi->fb.var.sync		= inf->sync;
	fbi->fb.var.grayscale		= inf->cmap_greyscale;
	fbi->state			= C_STARTUP;
	fbi->task_state			= (u_char)-1;
	fbi->fb.fix.smem_len		= inf->xres * inf->yres *
					  inf->bpp / 8;
	fbi->inf			= inf;

	/* Copy the RGB bitfield overrides */
	for (i = 0; i < NR_RGB; i++)
		if (inf->rgb[i])
			fbi->rgb[i] = inf->rgb[i];

	init_waitqueue_head(&fbi->ctrlr_wait);
	INIT_WORK(&fbi->task, sa1100fb_task);
	mutex_init(&fbi->ctrlr_lock);

	return fbi;
}