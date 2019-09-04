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
typedef  unsigned int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; } ;
struct TYPE_3__ {int visual; } ;
struct fb_info {unsigned int* pseudo_palette; TYPE_2__ var; TYPE_1__ fix; } ;

/* Variables and functions */
#define  FB_VISUAL_TRUECOLOR 128 
 unsigned int chan_to_field (unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nuc900fb_setcolreg(unsigned regno,
			       unsigned red, unsigned green, unsigned blue,
			       unsigned transp, struct fb_info *info)
{
	unsigned int val;

	switch (info->fix.visual) {
	case FB_VISUAL_TRUECOLOR:
		/* true-colour, use pseuo-palette */
		if (regno < 16) {
			u32 *pal = info->pseudo_palette;

			val  = chan_to_field(red, &info->var.red);
			val |= chan_to_field(green, &info->var.green);
			val |= chan_to_field(blue, &info->var.blue);
			pal[regno] = val;
		}
		break;

	default:
		return 1;   /* unknown type */
	}
	return 0;
}