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
struct TYPE_9__ {scalar_t__ length; scalar_t__ offset; } ;
struct TYPE_8__ {int length; scalar_t__ offset; } ;
struct TYPE_7__ {int offset; int length; } ;
struct TYPE_6__ {int offset; int length; } ;
struct fb_var_screeninfo {int xres; int yres; int bits_per_pixel; TYPE_4__ transp; TYPE_3__ blue; TYPE_2__ green; TYPE_1__ red; } ;
struct TYPE_10__ {int smem_len; } ;
struct fb_info {TYPE_5__ fix; } ;

/* Variables and functions */
 int EINVAL ; 
 int lx_get_pitch (int,int) ; 

__attribute__((used)) static int lxfb_check_var(struct fb_var_screeninfo *var, struct fb_info *info)
{
	if (var->xres > 1920 || var->yres > 1440)
		return -EINVAL;

	if (var->bits_per_pixel == 32) {
		var->red.offset   = 16; var->red.length   = 8;
		var->green.offset =  8; var->green.length = 8;
		var->blue.offset  =  0; var->blue.length  = 8;
	} else if (var->bits_per_pixel == 16) {
		var->red.offset   = 11; var->red.length   = 5;
		var->green.offset =  5; var->green.length = 6;
		var->blue.offset  =  0; var->blue.length  = 5;
	} else if (var->bits_per_pixel == 8) {
		var->red.offset   = 0; var->red.length   = 8;
		var->green.offset = 0; var->green.length = 8;
		var->blue.offset  = 0; var->blue.length  = 8;
	} else
		return -EINVAL;

	var->transp.offset = 0; var->transp.length = 0;

	/* Enough video memory? */
	if ((lx_get_pitch(var->xres, var->bits_per_pixel) * var->yres)
	    > info->fix.smem_len)
	  return -EINVAL;

	return 0;
}