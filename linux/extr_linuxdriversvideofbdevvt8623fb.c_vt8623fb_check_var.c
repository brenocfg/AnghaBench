#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fb_var_screeninfo {int xres; int xres_virtual; int yres; int yres_virtual; int bits_per_pixel; int vmode; } ;
struct fb_info {int screen_size; int /*<<< orphan*/  node; } ;
struct TYPE_3__ {int xresstep; } ;

/* Variables and functions */
 int EINVAL ; 
 int FB_VMODE_INTERLACED ; 
 int /*<<< orphan*/  fb_err (struct fb_info*,char*,...) ; 
 int svga_check_timings (int /*<<< orphan*/ *,struct fb_var_screeninfo*,int /*<<< orphan*/ ) ; 
 int svga_match_format (TYPE_1__*,struct fb_var_screeninfo*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vt8623_timing_regs ; 
 TYPE_1__* vt8623fb_formats ; 

__attribute__((used)) static int vt8623fb_check_var(struct fb_var_screeninfo *var, struct fb_info *info)
{
	int rv, mem, step;

	/* Find appropriate format */
	rv = svga_match_format (vt8623fb_formats, var, NULL);
	if (rv < 0)
	{
		fb_err(info, "unsupported mode requested\n");
		return rv;
	}

	/* Do not allow to have real resoulution larger than virtual */
	if (var->xres > var->xres_virtual)
		var->xres_virtual = var->xres;

	if (var->yres > var->yres_virtual)
		var->yres_virtual = var->yres;

	/* Round up xres_virtual to have proper alignment of lines */
	step = vt8623fb_formats[rv].xresstep - 1;
	var->xres_virtual = (var->xres_virtual+step) & ~step;

	/* Check whether have enough memory */
	mem = ((var->bits_per_pixel * var->xres_virtual) >> 3) * var->yres_virtual;
	if (mem > info->screen_size)
	{
		fb_err(info, "not enough framebuffer memory (%d kB requested, %d kB available)\n",
		       mem >> 10, (unsigned int) (info->screen_size >> 10));
		return -EINVAL;
	}

	/* Text mode is limited to 256 kB of memory */
	if ((var->bits_per_pixel == 0) && (mem > (256*1024)))
	{
		fb_err(info, "text framebuffer size too large (%d kB requested, 256 kB possible)\n",
		       mem >> 10);
		return -EINVAL;
	}

	rv = svga_check_timings (&vt8623_timing_regs, var, info->node);
	if (rv < 0)
	{
		fb_err(info, "invalid timings requested\n");
		return rv;
	}

	/* Interlaced mode not supported */
	if (var->vmode & FB_VMODE_INTERLACED)
		return -EINVAL;

	return 0;
}