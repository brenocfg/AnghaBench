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
typedef  int /*<<< orphan*/  u16 ;
struct s3fb_info {scalar_t__ chip; } ;
struct fb_var_screeninfo {int xres; int xres_virtual; int yres; int yres_virtual; int bits_per_pixel; int /*<<< orphan*/  pixclock; } ;
struct fb_info {int screen_size; int /*<<< orphan*/  node; struct s3fb_info* par; } ;
struct TYPE_3__ {int xresstep; } ;

/* Variables and functions */
 scalar_t__ CHIP_988_VIRGE_VX ; 
 int EINVAL ; 
 int /*<<< orphan*/  PICOS2KHZ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fb_err (struct fb_info*,char*,...) ; 
 int /*<<< orphan*/  s3_pll ; 
 int /*<<< orphan*/  s3_timing_regs ; 
 TYPE_1__* s3fb_formats ; 
 int svga_check_timings (int /*<<< orphan*/ *,struct fb_var_screeninfo*,int /*<<< orphan*/ ) ; 
 int svga_compute_pll (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int svga_match_format (TYPE_1__*,struct fb_var_screeninfo*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int s3fb_check_var(struct fb_var_screeninfo *var, struct fb_info *info)
{
	struct s3fb_info *par = info->par;
	int rv, mem, step;
	u16 m, n, r;

	/* Find appropriate format */
	rv = svga_match_format (s3fb_formats, var, NULL);

	/* 32bpp mode is not supported on VIRGE VX,
	   24bpp is not supported on others */
	if ((par->chip == CHIP_988_VIRGE_VX) ? (rv == 7) : (rv == 6))
		rv = -EINVAL;

	if (rv < 0) {
		fb_err(info, "unsupported mode requested\n");
		return rv;
	}

	/* Do not allow to have real resoulution larger than virtual */
	if (var->xres > var->xres_virtual)
		var->xres_virtual = var->xres;

	if (var->yres > var->yres_virtual)
		var->yres_virtual = var->yres;

	/* Round up xres_virtual to have proper alignment of lines */
	step = s3fb_formats[rv].xresstep - 1;
	var->xres_virtual = (var->xres_virtual+step) & ~step;

	/* Check whether have enough memory */
	mem = ((var->bits_per_pixel * var->xres_virtual) >> 3) * var->yres_virtual;
	if (mem > info->screen_size) {
		fb_err(info, "not enough framebuffer memory (%d kB requested , %u kB available)\n",
		       mem >> 10, (unsigned int) (info->screen_size >> 10));
		return -EINVAL;
	}

	rv = svga_check_timings (&s3_timing_regs, var, info->node);
	if (rv < 0) {
		fb_err(info, "invalid timings requested\n");
		return rv;
	}

	rv = svga_compute_pll(&s3_pll, PICOS2KHZ(var->pixclock), &m, &n, &r,
				info->node);
	if (rv < 0) {
		fb_err(info, "invalid pixclock value requested\n");
		return rv;
	}

	return 0;
}