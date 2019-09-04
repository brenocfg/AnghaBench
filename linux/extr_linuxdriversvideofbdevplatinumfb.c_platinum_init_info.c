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
struct fb_info_platinum {scalar_t__ total_vram; scalar_t__ frame_buffer_phys; int /*<<< orphan*/  platinum_regs_phys; scalar_t__ frame_buffer; int /*<<< orphan*/  pseudo_palette; } ;
struct TYPE_2__ {int mmio_len; int /*<<< orphan*/  accel; scalar_t__ type_aux; scalar_t__ ypanstep; scalar_t__ xpanstep; scalar_t__ ywrapstep; scalar_t__ smem_len; scalar_t__ smem_start; int /*<<< orphan*/  type; int /*<<< orphan*/  mmio_start; int /*<<< orphan*/  id; } ;
struct fb_info {TYPE_1__ fix; int /*<<< orphan*/  cmap; scalar_t__ screen_base; int /*<<< orphan*/  flags; int /*<<< orphan*/  pseudo_palette; int /*<<< orphan*/ * fbops; } ;

/* Variables and functions */
 int /*<<< orphan*/  FBINFO_DEFAULT ; 
 int /*<<< orphan*/  FB_ACCEL_NONE ; 
 int /*<<< orphan*/  FB_TYPE_PACKED_PIXELS ; 
 int /*<<< orphan*/  fb_alloc_cmap (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platinumfb_ops ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void platinum_init_info(struct fb_info *info,
			       struct fb_info_platinum *pinfo)
{
	/* Fill fb_info */
	info->fbops = &platinumfb_ops;
	info->pseudo_palette = pinfo->pseudo_palette;
        info->flags = FBINFO_DEFAULT;
	info->screen_base = pinfo->frame_buffer + 0x20;

	fb_alloc_cmap(&info->cmap, 256, 0);

	/* Fill fix common fields */
	strcpy(info->fix.id, "platinum");
	info->fix.mmio_start = pinfo->platinum_regs_phys;
	info->fix.mmio_len = 0x1000;
	info->fix.type = FB_TYPE_PACKED_PIXELS;
	info->fix.smem_start = pinfo->frame_buffer_phys + 0x20; /* will be updated later */
	info->fix.smem_len = pinfo->total_vram - 0x20;
        info->fix.ywrapstep = 0;
	info->fix.xpanstep = 0;
	info->fix.ypanstep = 0;
        info->fix.type_aux = 0;
        info->fix.accel = FB_ACCEL_NONE;
}