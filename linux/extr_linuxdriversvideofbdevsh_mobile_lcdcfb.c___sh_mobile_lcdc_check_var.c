#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sh_mobile_lcdc_format_info {int bpp; int /*<<< orphan*/  yuv; } ;
struct TYPE_9__ {int offset; int length; scalar_t__ msb_right; } ;
struct TYPE_8__ {int length; scalar_t__ msb_right; scalar_t__ offset; } ;
struct TYPE_7__ {int offset; int length; scalar_t__ msb_right; } ;
struct TYPE_6__ {int offset; int length; scalar_t__ msb_right; } ;
struct fb_var_screeninfo {scalar_t__ xres; scalar_t__ yres; scalar_t__ xres_virtual; scalar_t__ yres_virtual; int bits_per_pixel; scalar_t__ colorspace; TYPE_4__ transp; TYPE_3__ blue; TYPE_2__ green; TYPE_1__ red; int /*<<< orphan*/  grayscale; } ;
struct TYPE_10__ {int smem_len; } ;
struct fb_info {TYPE_5__ fix; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MAX_XRES ; 
 scalar_t__ MAX_YRES ; 
 scalar_t__ V4L2_COLORSPACE_JPEG ; 
 scalar_t__ V4L2_COLORSPACE_REC709 ; 
 scalar_t__ V4L2_COLORSPACE_SRGB ; 
 struct sh_mobile_lcdc_format_info* sh_mobile_format_info (int /*<<< orphan*/ ) ; 
 scalar_t__ sh_mobile_format_is_fourcc (struct fb_var_screeninfo*) ; 

__attribute__((used)) static int __sh_mobile_lcdc_check_var(struct fb_var_screeninfo *var,
				      struct fb_info *info)
{
	if (var->xres > MAX_XRES || var->yres > MAX_YRES)
		return -EINVAL;

	/* Make sure the virtual resolution is at least as big as the visible
	 * resolution.
	 */
	if (var->xres_virtual < var->xres)
		var->xres_virtual = var->xres;
	if (var->yres_virtual < var->yres)
		var->yres_virtual = var->yres;

	if (sh_mobile_format_is_fourcc(var)) {
		const struct sh_mobile_lcdc_format_info *format;

		format = sh_mobile_format_info(var->grayscale);
		if (format == NULL)
			return -EINVAL;
		var->bits_per_pixel = format->bpp;

		/* Default to RGB and JPEG color-spaces for RGB and YUV formats
		 * respectively.
		 */
		if (!format->yuv)
			var->colorspace = V4L2_COLORSPACE_SRGB;
		else if (var->colorspace != V4L2_COLORSPACE_REC709)
			var->colorspace = V4L2_COLORSPACE_JPEG;
	} else {
		if (var->bits_per_pixel <= 16) {		/* RGB 565 */
			var->bits_per_pixel = 16;
			var->red.offset = 11;
			var->red.length = 5;
			var->green.offset = 5;
			var->green.length = 6;
			var->blue.offset = 0;
			var->blue.length = 5;
			var->transp.offset = 0;
			var->transp.length = 0;
		} else if (var->bits_per_pixel <= 24) {		/* RGB 888 */
			var->bits_per_pixel = 24;
			var->red.offset = 16;
			var->red.length = 8;
			var->green.offset = 8;
			var->green.length = 8;
			var->blue.offset = 0;
			var->blue.length = 8;
			var->transp.offset = 0;
			var->transp.length = 0;
		} else if (var->bits_per_pixel <= 32) {		/* RGBA 888 */
			var->bits_per_pixel = 32;
			var->red.offset = 16;
			var->red.length = 8;
			var->green.offset = 8;
			var->green.length = 8;
			var->blue.offset = 0;
			var->blue.length = 8;
			var->transp.offset = 24;
			var->transp.length = 8;
		} else
			return -EINVAL;

		var->red.msb_right = 0;
		var->green.msb_right = 0;
		var->blue.msb_right = 0;
		var->transp.msb_right = 0;
	}

	/* Make sure we don't exceed our allocated memory. */
	if (var->xres_virtual * var->yres_virtual * var->bits_per_pixel / 8 >
	    info->fix.smem_len)
		return -EINVAL;

	return 0;
}