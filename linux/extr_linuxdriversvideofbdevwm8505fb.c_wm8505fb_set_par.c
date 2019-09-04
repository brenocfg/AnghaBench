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
struct wm8505fb_info {int contrast; scalar_t__ regbase; } ;
struct TYPE_8__ {int length; scalar_t__ msb_right; scalar_t__ offset; } ;
struct TYPE_7__ {int offset; int length; scalar_t__ msb_right; } ;
struct TYPE_6__ {int offset; int length; scalar_t__ msb_right; } ;
struct TYPE_10__ {int bits_per_pixel; int xres_virtual; TYPE_3__ blue; TYPE_2__ green; TYPE_1__ red; } ;
struct TYPE_9__ {int line_length; void* visual; } ;
struct fb_info {TYPE_5__ var; TYPE_4__ fix; } ;

/* Variables and functions */
 int EINVAL ; 
 void* FB_VISUAL_TRUECOLOR ; 
 scalar_t__ WMT_GOVR_CONTRAST ; 
 struct wm8505fb_info* to_wm8505fb_info (struct fb_info*) ; 
 int /*<<< orphan*/  wm8505fb_set_timing (struct fb_info*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int wm8505fb_set_par(struct fb_info *info)
{
	struct wm8505fb_info *fbi = to_wm8505fb_info(info);

	if (!fbi)
		return -EINVAL;

	if (info->var.bits_per_pixel == 32) {
		info->var.red.offset = 16;
		info->var.red.length = 8;
		info->var.red.msb_right = 0;
		info->var.green.offset = 8;
		info->var.green.length = 8;
		info->var.green.msb_right = 0;
		info->var.blue.offset = 0;
		info->var.blue.length = 8;
		info->var.blue.msb_right = 0;
		info->fix.visual = FB_VISUAL_TRUECOLOR;
		info->fix.line_length = info->var.xres_virtual << 2;
	} else if (info->var.bits_per_pixel == 16) {
		info->var.red.offset = 11;
		info->var.red.length = 5;
		info->var.red.msb_right = 0;
		info->var.green.offset = 5;
		info->var.green.length = 6;
		info->var.green.msb_right = 0;
		info->var.blue.offset = 0;
		info->var.blue.length = 5;
		info->var.blue.msb_right = 0;
		info->fix.visual = FB_VISUAL_TRUECOLOR;
		info->fix.line_length = info->var.xres_virtual << 1;
	}

	wm8505fb_set_timing(info);

	writel(fbi->contrast<<16 | fbi->contrast<<8 | fbi->contrast,
		fbi->regbase + WMT_GOVR_CONTRAST);

	return 0;
}