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
struct TYPE_8__ {int length; scalar_t__ offset; } ;
struct TYPE_7__ {int length; scalar_t__ offset; } ;
struct TYPE_6__ {scalar_t__ length; int offset; } ;
struct TYPE_5__ {int length; scalar_t__ offset; } ;
struct fb_var_screeninfo {int bits_per_pixel; TYPE_4__ blue; TYPE_3__ red; TYPE_2__ transp; TYPE_1__ green; } ;

/* Variables and functions */
 int EINVAL ; 
 int PIXFMT_BGR565 ; 
 int PIXFMT_BGR888PACK ; 
 int PIXFMT_BGR888UNPACK ; 
 int PIXFMT_BGRA888 ; 
 int PIXFMT_PSEUDOCOLOR ; 
 int PIXFMT_RGB565 ; 
 int PIXFMT_RGB888PACK ; 
 int PIXFMT_RGB888UNPACK ; 
 int PIXFMT_RGBA888 ; 
 int PIXFMT_UYVY ; 
 int PIXFMT_VYUY ; 
 int PIXFMT_YUV420P ; 
 int PIXFMT_YUV422P ; 
 int PIXFMT_YUYV ; 
 int PIXFMT_YVU420P ; 
 int PIXFMT_YVU422P ; 

__attribute__((used)) static int var_to_pixfmt(struct fb_var_screeninfo *var)
{
	/*
	 * Pseudocolor mode?
	 */
	if (var->bits_per_pixel == 8)
		return PIXFMT_PSEUDOCOLOR;

	/*
	 * Check for YUV422PLANAR.
	 */
	if (var->bits_per_pixel == 16 && var->red.length == 8 &&
			var->green.length == 4 && var->blue.length == 4) {
		if (var->green.offset >= var->blue.offset)
			return PIXFMT_YUV422P;
		else
			return PIXFMT_YVU422P;
	}

	/*
	 * Check for YUV420PLANAR.
	 */
	if (var->bits_per_pixel == 12 && var->red.length == 8 &&
			var->green.length == 2 && var->blue.length == 2) {
		if (var->green.offset >= var->blue.offset)
			return PIXFMT_YUV420P;
		else
			return PIXFMT_YVU420P;
	}

	/*
	 * Check for YUV422PACK.
	 */
	if (var->bits_per_pixel == 16 && var->red.length == 16 &&
			var->green.length == 16 && var->blue.length == 16) {
		if (var->red.offset == 0)
			return PIXFMT_YUYV;
		else if (var->green.offset >= var->blue.offset)
			return PIXFMT_UYVY;
		else
			return PIXFMT_VYUY;
	}

	/*
	 * Check for 565/1555.
	 */
	if (var->bits_per_pixel == 16 && var->red.length <= 5 &&
			var->green.length <= 6 && var->blue.length <= 5) {
		if (var->transp.length == 0) {
			if (var->red.offset >= var->blue.offset)
				return PIXFMT_RGB565;
			else
				return PIXFMT_BGR565;
		}
	}

	/*
	 * Check for 888/A888.
	 */
	if (var->bits_per_pixel <= 32 && var->red.length <= 8 &&
			var->green.length <= 8 && var->blue.length <= 8) {
		if (var->bits_per_pixel == 24 && var->transp.length == 0) {
			if (var->red.offset >= var->blue.offset)
				return PIXFMT_RGB888PACK;
			else
				return PIXFMT_BGR888PACK;
		}

		if (var->bits_per_pixel == 32 && var->transp.offset == 24) {
			if (var->red.offset >= var->blue.offset)
				return PIXFMT_RGBA888;
			else
				return PIXFMT_BGRA888;
		} else {
			if (var->red.offset >= var->blue.offset)
				return PIXFMT_RGB888UNPACK;
			else
				return PIXFMT_BGR888UNPACK;
		}

		/* fall through */
	}

	return -EINVAL;
}