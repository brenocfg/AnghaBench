#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {unsigned int offset; int /*<<< orphan*/  length; } ;
struct TYPE_10__ {unsigned int offset; int /*<<< orphan*/  length; } ;
struct TYPE_9__ {unsigned int offset; int /*<<< orphan*/  length; } ;
struct TYPE_8__ {unsigned int offset; int /*<<< orphan*/  length; } ;
struct TYPE_12__ {TYPE_5__ transp; TYPE_4__ blue; TYPE_3__ green; TYPE_2__ red; } ;
struct TYPE_7__ {int visual; } ;
struct fb_info {unsigned int* pseudo_palette; TYPE_6__ var; TYPE_1__ fix; struct ep93xx_fbi* par; } ;
struct ep93xx_fbi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EP93XXFB_COLOR_LUT ; 
 int /*<<< orphan*/  EP93XXFB_LUT_SW_CONTROL ; 
 unsigned int EP93XXFB_LUT_SW_CONTROL_SSTAT ; 
 unsigned int EP93XXFB_LUT_SW_CONTROL_SWTCH ; 
#define  FB_VISUAL_PSEUDOCOLOR 129 
#define  FB_VISUAL_TRUECOLOR 128 
 unsigned int ep93xxfb_convert_color (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int ep93xxfb_readl (struct ep93xx_fbi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ep93xxfb_writel (struct ep93xx_fbi*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ep93xxfb_setcolreg(unsigned int regno, unsigned int red,
			      unsigned int green, unsigned int blue,
			      unsigned int transp, struct fb_info *info)
{
	struct ep93xx_fbi *fbi = info->par;
	unsigned int *pal = info->pseudo_palette;
	unsigned int ctrl, i, rgb, lut_current, lut_stat;

	switch (info->fix.visual) {
	case FB_VISUAL_PSEUDOCOLOR:
		if (regno > 255)
			return 1;
		rgb = ((red & 0xff00) << 8) | (green & 0xff00) |
			((blue & 0xff00) >> 8);

		pal[regno] = rgb;
		ep93xxfb_writel(fbi, rgb, (EP93XXFB_COLOR_LUT + (regno << 2)));
		ctrl = ep93xxfb_readl(fbi, EP93XXFB_LUT_SW_CONTROL);
		lut_stat = !!(ctrl & EP93XXFB_LUT_SW_CONTROL_SSTAT);
		lut_current = !!(ctrl & EP93XXFB_LUT_SW_CONTROL_SWTCH);

		if (lut_stat == lut_current) {
			for (i = 0; i < 256; i++) {
				ep93xxfb_writel(fbi, pal[i],
					EP93XXFB_COLOR_LUT + (i << 2));
			}

			ep93xxfb_writel(fbi,
					ctrl ^ EP93XXFB_LUT_SW_CONTROL_SWTCH,
					EP93XXFB_LUT_SW_CONTROL);
		}
		break;

	case FB_VISUAL_TRUECOLOR:
		if (regno > 16)
			return 1;

		red = ep93xxfb_convert_color(red, info->var.red.length);
		green = ep93xxfb_convert_color(green, info->var.green.length);
		blue = ep93xxfb_convert_color(blue, info->var.blue.length);
		transp = ep93xxfb_convert_color(transp,
						info->var.transp.length);

		pal[regno] = (red << info->var.red.offset) |
			(green << info->var.green.offset) |
			(blue << info->var.blue.offset) |
			(transp << info->var.transp.offset);
		break;

	default:
		return 1;
	}

	return 0;
}