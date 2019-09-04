#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sgi_gbe {int dummy; } ;
struct fb_var_screeninfo {int bits_per_pixel; int xres_virtual; } ;
struct fb_fix_screeninfo {unsigned long smem_start; int line_length; int mmio_len; int /*<<< orphan*/  mmio_start; scalar_t__ ypanstep; scalar_t__ xpanstep; scalar_t__ ywrapstep; int /*<<< orphan*/  visual; int /*<<< orphan*/  accel; scalar_t__ type_aux; int /*<<< orphan*/  type; int /*<<< orphan*/  smem_len; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB_ACCEL_NONE ; 
 int /*<<< orphan*/  FB_TYPE_PACKED_PIXELS ; 
 int /*<<< orphan*/  FB_VISUAL_PSEUDOCOLOR ; 
 int /*<<< orphan*/  FB_VISUAL_TRUECOLOR ; 
 int /*<<< orphan*/  GBE_BASE ; 
 scalar_t__ gbe_mem ; 
 int /*<<< orphan*/  gbe_mem_size ; 
 int /*<<< orphan*/  memset (struct fb_fix_screeninfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void gbefb_encode_fix(struct fb_fix_screeninfo *fix,
			     struct fb_var_screeninfo *var)
{
	memset(fix, 0, sizeof(struct fb_fix_screeninfo));
	strcpy(fix->id, "SGI GBE");
	fix->smem_start = (unsigned long) gbe_mem;
	fix->smem_len = gbe_mem_size;
	fix->type = FB_TYPE_PACKED_PIXELS;
	fix->type_aux = 0;
	fix->accel = FB_ACCEL_NONE;
	switch (var->bits_per_pixel) {
	case 8:
		fix->visual = FB_VISUAL_PSEUDOCOLOR;
		break;
	default:
		fix->visual = FB_VISUAL_TRUECOLOR;
		break;
	}
	fix->ywrapstep = 0;
	fix->xpanstep = 0;
	fix->ypanstep = 0;
	fix->line_length = var->xres_virtual * var->bits_per_pixel / 8;
	fix->mmio_start = GBE_BASE;
	fix->mmio_len = sizeof(struct sgi_gbe);
}