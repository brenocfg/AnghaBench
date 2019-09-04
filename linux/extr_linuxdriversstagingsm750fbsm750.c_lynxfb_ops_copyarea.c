#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  (* de_copyarea ) (TYPE_4__*,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct sm750_dev {int /*<<< orphan*/  slock; TYPE_4__ accel; } ;
struct TYPE_5__ {unsigned int oScreen; } ;
struct lynxfb_par {TYPE_1__ crtc; struct sm750_dev* dev; } ;
struct TYPE_7__ {int bits_per_pixel; } ;
struct TYPE_6__ {unsigned int line_length; } ;
struct fb_info {TYPE_3__ var; TYPE_2__ fix; struct lynxfb_par* par; } ;
struct fb_copyarea {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  dy; int /*<<< orphan*/  dx; int /*<<< orphan*/  sy; int /*<<< orphan*/  sx; } ;

/* Variables and functions */
 int /*<<< orphan*/  HW_ROP2_COPY ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lynxfb_ops_copyarea(struct fb_info *info,
				const struct fb_copyarea *region)
{
	struct lynxfb_par *par;
	struct sm750_dev *sm750_dev;
	unsigned int base, pitch, Bpp;

	par = info->par;
	sm750_dev = par->dev;

	/*
	 * each time 2d function begin to work,below three variable always need
	 * be set, seems we can put them together in some place
	 */
	base = par->crtc.oScreen;
	pitch = info->fix.line_length;
	Bpp = info->var.bits_per_pixel >> 3;

	/*
	 * If not use spin_lock, system will die if user load driver
	 * and immediately unload driver frequently (dual)
	 * since they fb_count could change during the lifetime of
	 * this lock, we are holding it for all cases.
	 */
	spin_lock(&sm750_dev->slock);

	sm750_dev->accel.de_copyarea(&sm750_dev->accel,
				     base, pitch, region->sx, region->sy,
				     base, pitch, Bpp, region->dx, region->dy,
				     region->width, region->height,
				     HW_ROP2_COPY);
	spin_unlock(&sm750_dev->slock);
}