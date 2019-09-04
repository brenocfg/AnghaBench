#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int bits_per_pixel; int /*<<< orphan*/  xres; } ;
struct TYPE_3__ {int /*<<< orphan*/  line_length; int /*<<< orphan*/  visual; } ;
struct fb_info {TYPE_2__ var; TYPE_1__ fix; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB_VISUAL_PSEUDOCOLOR ; 
 int /*<<< orphan*/  FB_VISUAL_TRUECOLOR ; 
 int /*<<< orphan*/  gx_line_delta (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gx_set_mode (struct fb_info*) ; 

__attribute__((used)) static int gxfb_set_par(struct fb_info *info)
{
	if (info->var.bits_per_pixel > 8)
		info->fix.visual = FB_VISUAL_TRUECOLOR;
	else
		info->fix.visual = FB_VISUAL_PSEUDOCOLOR;

	info->fix.line_length = gx_line_delta(info->var.xres, info->var.bits_per_pixel);

	gx_set_mode(info);

	return 0;
}