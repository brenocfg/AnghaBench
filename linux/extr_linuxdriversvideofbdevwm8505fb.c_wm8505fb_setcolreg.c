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
typedef  unsigned int u32 ;
struct TYPE_7__ {int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; } ;
struct TYPE_6__ {int visual; } ;
struct TYPE_8__ {TYPE_3__ var; TYPE_2__ fix; } ;
struct wm8505fb_info {TYPE_4__ fb; } ;
struct TYPE_5__ {scalar_t__ grayscale; } ;
struct fb_info {unsigned int* pseudo_palette; TYPE_1__ var; } ;

/* Variables and functions */
 int EINVAL ; 
#define  FB_VISUAL_TRUECOLOR 128 
 unsigned int chan_to_field (unsigned int,int /*<<< orphan*/ *) ; 
 struct wm8505fb_info* to_wm8505fb_info (struct fb_info*) ; 

__attribute__((used)) static int wm8505fb_setcolreg(unsigned regno, unsigned red, unsigned green,
			   unsigned blue, unsigned transp,
			   struct fb_info *info) {
	struct wm8505fb_info *fbi = to_wm8505fb_info(info);
	int ret = 1;
	unsigned int val;
	if (regno >= 256)
		return -EINVAL;

	if (info->var.grayscale)
		red = green = blue =
			(19595 * red + 38470 * green + 7471 * blue) >> 16;

	switch (fbi->fb.fix.visual) {
	case FB_VISUAL_TRUECOLOR:
		if (regno < 16) {
			u32 *pal = info->pseudo_palette;

			val  = chan_to_field(red, &fbi->fb.var.red);
			val |= chan_to_field(green, &fbi->fb.var.green);
			val |= chan_to_field(blue, &fbi->fb.var.blue);

			pal[regno] = val;
			ret = 0;
		}
		break;
	}

	return ret;
}