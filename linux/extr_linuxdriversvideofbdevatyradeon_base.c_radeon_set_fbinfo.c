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
struct radeonfb_info {int /*<<< orphan*/  mmio_base_phys; int /*<<< orphan*/  video_ram; int /*<<< orphan*/  fb_base_phys; int /*<<< orphan*/  name; int /*<<< orphan*/  mapped_vram; int /*<<< orphan*/  fb_base; int /*<<< orphan*/  pseudo_palette; struct fb_info* info; } ;
struct TYPE_2__ {int xpanstep; int ypanstep; int /*<<< orphan*/  accel; int /*<<< orphan*/  mmio_len; int /*<<< orphan*/  mmio_start; scalar_t__ type_aux; scalar_t__ ywrapstep; int /*<<< orphan*/  visual; int /*<<< orphan*/  type; int /*<<< orphan*/  smem_len; int /*<<< orphan*/  smem_start; int /*<<< orphan*/  id; } ;
struct fb_info {int flags; int /*<<< orphan*/  cmap; TYPE_1__ fix; int /*<<< orphan*/  screen_size; int /*<<< orphan*/  screen_base; int /*<<< orphan*/ * fbops; int /*<<< orphan*/  pseudo_palette; struct radeonfb_info* par; } ;

/* Variables and functions */
 int FBINFO_DEFAULT ; 
 int FBINFO_HWACCEL_COPYAREA ; 
 int FBINFO_HWACCEL_DISABLED ; 
 int FBINFO_HWACCEL_FILLRECT ; 
 int FBINFO_HWACCEL_XPAN ; 
 int FBINFO_HWACCEL_YPAN ; 
 int /*<<< orphan*/  FB_ACCEL_ATI_RADEON ; 
 int /*<<< orphan*/  FB_TYPE_PACKED_PIXELS ; 
 int /*<<< orphan*/  FB_VISUAL_PSEUDOCOLOR ; 
 int /*<<< orphan*/  RADEON_REGSIZE ; 
 int /*<<< orphan*/  fb_alloc_cmap (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ noaccel ; 
 int /*<<< orphan*/  radeonfb_ops ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int radeon_set_fbinfo(struct radeonfb_info *rinfo)
{
	struct fb_info *info = rinfo->info;

	info->par = rinfo;
	info->pseudo_palette = rinfo->pseudo_palette;
	info->flags = FBINFO_DEFAULT
		    | FBINFO_HWACCEL_COPYAREA
		    | FBINFO_HWACCEL_FILLRECT
		    | FBINFO_HWACCEL_XPAN
		    | FBINFO_HWACCEL_YPAN;
	info->fbops = &radeonfb_ops;
	info->screen_base = rinfo->fb_base;
	info->screen_size = rinfo->mapped_vram;
	/* Fill fix common fields */
	strlcpy(info->fix.id, rinfo->name, sizeof(info->fix.id));
        info->fix.smem_start = rinfo->fb_base_phys;
        info->fix.smem_len = rinfo->video_ram;
        info->fix.type = FB_TYPE_PACKED_PIXELS;
        info->fix.visual = FB_VISUAL_PSEUDOCOLOR;
        info->fix.xpanstep = 8;
        info->fix.ypanstep = 1;
        info->fix.ywrapstep = 0;
        info->fix.type_aux = 0;
        info->fix.mmio_start = rinfo->mmio_base_phys;
        info->fix.mmio_len = RADEON_REGSIZE;
	info->fix.accel = FB_ACCEL_ATI_RADEON;

	fb_alloc_cmap(&info->cmap, 256, 0);

	if (noaccel)
		info->flags |= FBINFO_HWACCEL_DISABLED;

        return 0;
}