#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u32 ;
struct TYPE_5__ {int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; scalar_t__ grayscale; } ;
struct TYPE_4__ {int visual; } ;
struct fb_info {unsigned int* pseudo_palette; TYPE_2__ var; TYPE_1__ fix; struct atmel_lcdfb_info* par; } ;
struct atmel_lcdfb_pdata {int /*<<< orphan*/  lcd_wiring_mode; } ;
struct atmel_lcdfb_info {TYPE_3__* config; struct atmel_lcdfb_pdata pdata; } ;
struct TYPE_6__ {int /*<<< orphan*/  have_intensity_bit; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMEL_LCDC_LUT (unsigned int) ; 
 int /*<<< orphan*/  ATMEL_LCDC_WIRING_RGB ; 
#define  FB_VISUAL_MONO01 130 
#define  FB_VISUAL_PSEUDOCOLOR 129 
#define  FB_VISUAL_TRUECOLOR 128 
 unsigned int chan_to_field (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lcdc_writel (struct atmel_lcdfb_info*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int atmel_lcdfb_setcolreg(unsigned int regno, unsigned int red,
			     unsigned int green, unsigned int blue,
			     unsigned int transp, struct fb_info *info)
{
	struct atmel_lcdfb_info *sinfo = info->par;
	struct atmel_lcdfb_pdata *pdata = &sinfo->pdata;
	unsigned int val;
	u32 *pal;
	int ret = 1;

	if (info->var.grayscale)
		red = green = blue = (19595 * red + 38470 * green
				      + 7471 * blue) >> 16;

	switch (info->fix.visual) {
	case FB_VISUAL_TRUECOLOR:
		if (regno < 16) {
			pal = info->pseudo_palette;

			val  = chan_to_field(red, &info->var.red);
			val |= chan_to_field(green, &info->var.green);
			val |= chan_to_field(blue, &info->var.blue);

			pal[regno] = val;
			ret = 0;
		}
		break;

	case FB_VISUAL_PSEUDOCOLOR:
		if (regno < 256) {
			if (sinfo->config->have_intensity_bit) {
				/* old style I+BGR:555 */
				val  = ((red   >> 11) & 0x001f);
				val |= ((green >>  6) & 0x03e0);
				val |= ((blue  >>  1) & 0x7c00);

				/*
				 * TODO: intensity bit. Maybe something like
				 *   ~(red[10] ^ green[10] ^ blue[10]) & 1
				 */
			} else {
				/* new style BGR:565 / RGB:565 */
				if (pdata->lcd_wiring_mode == ATMEL_LCDC_WIRING_RGB) {
					val  = ((blue >> 11) & 0x001f);
					val |= ((red  >>  0) & 0xf800);
				} else {
					val  = ((red  >> 11) & 0x001f);
					val |= ((blue >>  0) & 0xf800);
				}

				val |= ((green >>  5) & 0x07e0);
			}

			lcdc_writel(sinfo, ATMEL_LCDC_LUT(regno), val);
			ret = 0;
		}
		break;

	case FB_VISUAL_MONO01:
		if (regno < 2) {
			val = (regno == 0) ? 0x00 : 0x1F;
			lcdc_writel(sinfo, ATMEL_LCDC_LUT(regno), val);
			ret = 0;
		}
		break;

	}

	return ret;
}