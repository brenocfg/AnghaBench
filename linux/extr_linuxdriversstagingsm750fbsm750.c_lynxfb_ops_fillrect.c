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
typedef  size_t u32 ;
struct TYPE_8__ {int /*<<< orphan*/  (* de_fillrect ) (TYPE_4__*,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,unsigned int) ;} ;
struct sm750_dev {int /*<<< orphan*/  slock; TYPE_4__ accel; } ;
struct TYPE_5__ {unsigned int oScreen; } ;
struct lynxfb_par {TYPE_1__ crtc; struct sm750_dev* dev; } ;
struct TYPE_7__ {int bits_per_pixel; } ;
struct TYPE_6__ {unsigned int line_length; } ;
struct fb_info {scalar_t__ state; scalar_t__ pseudo_palette; TYPE_3__ var; TYPE_2__ fix; struct lynxfb_par* par; } ;
struct fb_fillrect {size_t color; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  dy; int /*<<< orphan*/  dx; int /*<<< orphan*/  rop; } ;

/* Variables and functions */
 scalar_t__ FBINFO_STATE_RUNNING ; 
 unsigned int HW_ROP2_COPY ; 
 unsigned int HW_ROP2_XOR ; 
 int /*<<< orphan*/  ROP_COPY ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,unsigned int) ; 

__attribute__((used)) static void lynxfb_ops_fillrect(struct fb_info *info,
				const struct fb_fillrect *region)
{
	struct lynxfb_par *par;
	struct sm750_dev *sm750_dev;
	unsigned int base, pitch, Bpp, rop;
	u32 color;

	if (info->state != FBINFO_STATE_RUNNING)
		return;

	par = info->par;
	sm750_dev = par->dev;

	/*
	 * each time 2d function begin to work,below three variable always need
	 * be set, seems we can put them together in some place
	 */
	base = par->crtc.oScreen;
	pitch = info->fix.line_length;
	Bpp = info->var.bits_per_pixel >> 3;

	color = (Bpp == 1) ? region->color :
		((u32 *)info->pseudo_palette)[region->color];
	rop = (region->rop != ROP_COPY) ? HW_ROP2_XOR : HW_ROP2_COPY;

	/*
	 * If not use spin_lock, system will die if user load driver
	 * and immediately unload driver frequently (dual)
	 * since they fb_count could change during the lifetime of
	 * this lock, we are holding it for all cases.
	 */
	spin_lock(&sm750_dev->slock);

	sm750_dev->accel.de_fillrect(&sm750_dev->accel,
				     base, pitch, Bpp,
				     region->dx, region->dy,
				     region->width, region->height,
				     color, rop);
	spin_unlock(&sm750_dev->slock);
}