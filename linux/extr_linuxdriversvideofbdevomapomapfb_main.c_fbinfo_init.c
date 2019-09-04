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
struct omapfb_device {int /*<<< orphan*/  dev; TYPE_1__* panel; int /*<<< orphan*/  pseudo_palette; } ;
struct fb_var_screeninfo {int /*<<< orphan*/  bits_per_pixel; int /*<<< orphan*/  rotate; void* yres_virtual; void* xres_virtual; void* yres; void* xres; int /*<<< orphan*/  accel_flags; } ;
struct fb_fix_screeninfo {int /*<<< orphan*/  id; } ;
struct fb_info {int /*<<< orphan*/  cmap; int /*<<< orphan*/  pseudo_palette; int /*<<< orphan*/  flags; int /*<<< orphan*/ * fbops; struct fb_fix_screeninfo fix; struct fb_var_screeninfo var; } ;
struct TYPE_2__ {int /*<<< orphan*/  bpp; } ;

/* Variables and functions */
 int /*<<< orphan*/  FBINFO_FLAG_DEFAULT ; 
 int /*<<< orphan*/  FB_ACCELF_TEXT ; 
 int /*<<< orphan*/  MODULE_NAME ; 
 scalar_t__ def_accel ; 
 int /*<<< orphan*/  def_rotate ; 
 void* def_vxres ; 
 void* def_vyres ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int fb_alloc_cmap (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omapfb_ops ; 
 int /*<<< orphan*/  set_fb_fix (struct fb_info*,int) ; 
 int /*<<< orphan*/  set_fb_var (struct fb_info*,struct fb_var_screeninfo*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fbinfo_init(struct omapfb_device *fbdev, struct fb_info *info)
{
	struct fb_var_screeninfo	*var = &info->var;
	struct fb_fix_screeninfo	*fix = &info->fix;
	int				r = 0;

	info->fbops = &omapfb_ops;
	info->flags = FBINFO_FLAG_DEFAULT;

	strncpy(fix->id, MODULE_NAME, sizeof(fix->id));

	info->pseudo_palette = fbdev->pseudo_palette;

	var->accel_flags  = def_accel ? FB_ACCELF_TEXT : 0;
	var->xres = def_vxres;
	var->yres = def_vyres;
	var->xres_virtual = def_vxres;
	var->yres_virtual = def_vyres;
	var->rotate	  = def_rotate;
	var->bits_per_pixel = fbdev->panel->bpp;

	set_fb_var(info, var);
	set_fb_fix(info, 1);

	r = fb_alloc_cmap(&info->cmap, 16, 0);
	if (r != 0)
		dev_err(fbdev->dev, "unable to allocate color map memory\n");

	return r;
}