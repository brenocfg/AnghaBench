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
typedef  int u_int ;
typedef  unsigned int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; scalar_t__ grayscale; } ;
struct TYPE_3__ {int visual; } ;
struct fb_info {unsigned int* pseudo_palette; TYPE_2__ var; TYPE_1__ fix; } ;

/* Variables and functions */
 int EINVAL ; 
#define  FB_VISUAL_PSEUDOCOLOR 130 
#define  FB_VISUAL_STATIC_PSEUDOCOLOR 129 
#define  FB_VISUAL_TRUECOLOR 128 
 unsigned int chan_to_field (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mxsfb_setcolreg(u_int regno, u_int red, u_int green, u_int blue,
		u_int transp, struct fb_info *fb_info)
{
	unsigned int val;
	int ret = -EINVAL;

	/*
	 * If greyscale is true, then we convert the RGB value
	 * to greyscale no matter what visual we are using.
	 */
	if (fb_info->var.grayscale)
		red = green = blue = (19595 * red + 38470 * green +
					7471 * blue) >> 16;

	switch (fb_info->fix.visual) {
	case FB_VISUAL_TRUECOLOR:
		/*
		 * 12 or 16-bit True Colour.  We encode the RGB value
		 * according to the RGB bitfield information.
		 */
		if (regno < 16) {
			u32 *pal = fb_info->pseudo_palette;

			val  = chan_to_field(red, &fb_info->var.red);
			val |= chan_to_field(green, &fb_info->var.green);
			val |= chan_to_field(blue, &fb_info->var.blue);

			pal[regno] = val;
			ret = 0;
		}
		break;

	case FB_VISUAL_STATIC_PSEUDOCOLOR:
	case FB_VISUAL_PSEUDOCOLOR:
		break;
	}

	return ret;
}