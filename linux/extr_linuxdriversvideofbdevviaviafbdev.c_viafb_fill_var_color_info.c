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
typedef  int u8 ;
struct TYPE_8__ {int length; int /*<<< orphan*/  offset; scalar_t__ msb_right; } ;
struct TYPE_7__ {int offset; int length; scalar_t__ msb_right; } ;
struct TYPE_6__ {int offset; int length; scalar_t__ msb_right; } ;
struct TYPE_5__ {scalar_t__ msb_right; scalar_t__ length; scalar_t__ offset; } ;
struct fb_var_screeninfo {int bits_per_pixel; TYPE_4__ blue; TYPE_3__ green; TYPE_2__ red; scalar_t__ nonstd; TYPE_1__ transp; scalar_t__ grayscale; } ;

/* Variables and functions */

__attribute__((used)) static void viafb_fill_var_color_info(struct fb_var_screeninfo *var, u8 depth)
{
	var->grayscale = 0;
	var->red.msb_right = 0;
	var->green.msb_right = 0;
	var->blue.msb_right = 0;
	var->transp.offset = 0;
	var->transp.length = 0;
	var->transp.msb_right = 0;
	var->nonstd = 0;
	switch (depth) {
	case 8:
		var->bits_per_pixel = 8;
		var->red.offset = 0;
		var->green.offset = 0;
		var->blue.offset = 0;
		var->red.length = 8;
		var->green.length = 8;
		var->blue.length = 8;
		break;
	case 15:
		var->bits_per_pixel = 16;
		var->red.offset = 10;
		var->green.offset = 5;
		var->blue.offset = 0;
		var->red.length = 5;
		var->green.length = 5;
		var->blue.length = 5;
		break;
	case 16:
		var->bits_per_pixel = 16;
		var->red.offset = 11;
		var->green.offset = 5;
		var->blue.offset = 0;
		var->red.length = 5;
		var->green.length = 6;
		var->blue.length = 5;
		break;
	case 24:
		var->bits_per_pixel = 32;
		var->red.offset = 16;
		var->green.offset = 8;
		var->blue.offset = 0;
		var->red.length = 8;
		var->green.length = 8;
		var->blue.length = 8;
		break;
	case 30:
		var->bits_per_pixel = 32;
		var->red.offset = 20;
		var->green.offset = 10;
		var->blue.offset = 0;
		var->red.length = 10;
		var->green.length = 10;
		var->blue.length = 10;
		break;
	}
}