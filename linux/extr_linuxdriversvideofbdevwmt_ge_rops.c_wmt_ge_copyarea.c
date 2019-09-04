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
struct TYPE_6__ {int bits_per_pixel; int xres_virtual; int yres_virtual; } ;
struct TYPE_5__ {int smem_start; } ;
struct fb_info {scalar_t__ state; TYPE_3__ var; TYPE_2__ fix; TYPE_1__* fbops; } ;
struct fb_copyarea {int sx; int sy; int width; int height; int dx; int dy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* fb_sync ) (struct fb_info*) ;} ;

/* Variables and functions */
 scalar_t__ FBINFO_STATE_RUNNING ; 
 scalar_t__ GE_COMMAND_OFF ; 
 scalar_t__ GE_DEPTH_OFF ; 
 scalar_t__ GE_DESTAREAH_OFF ; 
 scalar_t__ GE_DESTAREAW_OFF ; 
 scalar_t__ GE_DESTAREAX_OFF ; 
 scalar_t__ GE_DESTAREAY_OFF ; 
 scalar_t__ GE_DESTBASE_OFF ; 
 scalar_t__ GE_DESTDISPH_OFF ; 
 scalar_t__ GE_DESTDISPW_OFF ; 
 scalar_t__ GE_FIRE_OFF ; 
 scalar_t__ GE_ROPCODE_OFF ; 
 scalar_t__ GE_SRCAREAH_OFF ; 
 scalar_t__ GE_SRCAREAW_OFF ; 
 scalar_t__ GE_SRCAREAX_OFF ; 
 scalar_t__ GE_SRCAREAY_OFF ; 
 scalar_t__ GE_SRCBASE_OFF ; 
 scalar_t__ GE_SRCDISPH_OFF ; 
 scalar_t__ GE_SRCDISPW_OFF ; 
 scalar_t__ regbase ; 
 int /*<<< orphan*/  stub1 (struct fb_info*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

void wmt_ge_copyarea(struct fb_info *p, const struct fb_copyarea *area)
{
	if (p->state != FBINFO_STATE_RUNNING)
		return;

	if (p->fbops->fb_sync)
		p->fbops->fb_sync(p);

	writel(p->var.bits_per_pixel > 16 ? 3 :
	      (p->var.bits_per_pixel > 8 ? 1 : 0), regbase + GE_DEPTH_OFF);

	writel(p->fix.smem_start, regbase + GE_SRCBASE_OFF);
	writel(p->var.xres_virtual - 1, regbase + GE_SRCDISPW_OFF);
	writel(p->var.yres_virtual - 1, regbase + GE_SRCDISPH_OFF);
	writel(area->sx, regbase + GE_SRCAREAX_OFF);
	writel(area->sy, regbase + GE_SRCAREAY_OFF);
	writel(area->width - 1, regbase + GE_SRCAREAW_OFF);
	writel(area->height - 1, regbase + GE_SRCAREAH_OFF);

	writel(p->fix.smem_start, regbase + GE_DESTBASE_OFF);
	writel(p->var.xres_virtual - 1, regbase + GE_DESTDISPW_OFF);
	writel(p->var.yres_virtual - 1, regbase + GE_DESTDISPH_OFF);
	writel(area->dx, regbase + GE_DESTAREAX_OFF);
	writel(area->dy, regbase + GE_DESTAREAY_OFF);
	writel(area->width - 1, regbase + GE_DESTAREAW_OFF);
	writel(area->height - 1, regbase + GE_DESTAREAH_OFF);

	writel(0xcc, regbase + GE_ROPCODE_OFF);
	writel(1, regbase + GE_COMMAND_OFF);
	writel(1, regbase + GE_FIRE_OFF);
}