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
struct mxsfb_info {int /*<<< orphan*/  ld_intf_width; } ;
struct fb_bitfield {int dummy; } ;
struct fb_var_screeninfo {scalar_t__ xres; scalar_t__ yres; scalar_t__ xres_virtual; scalar_t__ yres_virtual; int bits_per_pixel; struct fb_bitfield transp; struct fb_bitfield blue; struct fb_bitfield green; struct fb_bitfield red; } ;
struct fb_info {struct mxsfb_info* par; } ;

/* Variables and functions */
 size_t BLUE ; 
 int EINVAL ; 
 size_t GREEN ; 
 scalar_t__ MIN_XRES ; 
 scalar_t__ MIN_YRES ; 
 size_t RED ; 
#define  STMLCDIF_16BIT 131 
#define  STMLCDIF_18BIT 130 
#define  STMLCDIF_24BIT 129 
#define  STMLCDIF_8BIT 128 
 size_t TRANSP ; 
 struct fb_bitfield* def_rgb565 ; 
 struct fb_bitfield* def_rgb888 ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int mxsfb_check_var(struct fb_var_screeninfo *var,
		struct fb_info *fb_info)
{
	struct mxsfb_info *host = fb_info->par;
	const struct fb_bitfield *rgb = NULL;

	if (var->xres < MIN_XRES)
		var->xres = MIN_XRES;
	if (var->yres < MIN_YRES)
		var->yres = MIN_YRES;

	var->xres_virtual = var->xres;

	var->yres_virtual = var->yres;

	switch (var->bits_per_pixel) {
	case 16:
		/* always expect RGB 565 */
		rgb = def_rgb565;
		break;
	case 32:
		switch (host->ld_intf_width) {
		case STMLCDIF_8BIT:
			pr_debug("Unsupported LCD bus width mapping\n");
			break;
		case STMLCDIF_16BIT:
		case STMLCDIF_18BIT:
		case STMLCDIF_24BIT:
			/* real 24 bit */
			rgb = def_rgb888;
			break;
		}
		break;
	default:
		pr_err("Unsupported colour depth: %u\n", var->bits_per_pixel);
		return -EINVAL;
	}

	/*
	 * Copy the RGB parameters for this display
	 * from the machine specific parameters.
	 */
	var->red    = rgb[RED];
	var->green  = rgb[GREEN];
	var->blue   = rgb[BLUE];
	var->transp = rgb[TRANSP];

	return 0;
}