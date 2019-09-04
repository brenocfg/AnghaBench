#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u8 ;
typedef  unsigned int u32 ;
struct TYPE_13__ {scalar_t__ Architecture; } ;
struct riva_par {unsigned int* palette; TYPE_5__ riva; } ;
struct TYPE_12__ {unsigned int offset; int length; } ;
struct TYPE_11__ {unsigned int offset; } ;
struct TYPE_10__ {unsigned int offset; } ;
struct TYPE_14__ {int bits_per_pixel; TYPE_4__ green; TYPE_3__ blue; TYPE_2__ red; scalar_t__ grayscale; } ;
struct TYPE_9__ {scalar_t__ visual; } ;
struct fb_info {TYPE_8__ var; scalar_t__ pseudo_palette; TYPE_1__ fix; struct riva_par* par; } ;
typedef  TYPE_5__ RIVA_HW_INST ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ FB_VISUAL_DIRECTCOLOR ; 
 scalar_t__ NV_ARCH_03 ; 
 unsigned int riva_get_cmap_len (TYPE_8__*) ; 
 int /*<<< orphan*/  riva_rclut (TYPE_5__*,unsigned int,unsigned int*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  riva_wclut (TYPE_5__*,unsigned int,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static int rivafb_setcolreg(unsigned regno, unsigned red, unsigned green,
			  unsigned blue, unsigned transp,
			  struct fb_info *info)
{
	struct riva_par *par = info->par;
	RIVA_HW_INST *chip = &par->riva;
	int i;

	if (regno >= riva_get_cmap_len(&info->var))
			return -EINVAL;

	if (info->var.grayscale) {
		/* gray = 0.30*R + 0.59*G + 0.11*B */
		red = green = blue =
		    (red * 77 + green * 151 + blue * 28) >> 8;
	}

	if (regno < 16 && info->fix.visual == FB_VISUAL_DIRECTCOLOR) {
		((u32 *) info->pseudo_palette)[regno] =
			(regno << info->var.red.offset) |
			(regno << info->var.green.offset) |
			(regno << info->var.blue.offset);
		/*
		 * The Riva128 2D engine requires color information in
		 * TrueColor format even if framebuffer is in DirectColor
		 */
		if (par->riva.Architecture == NV_ARCH_03) {
			switch (info->var.bits_per_pixel) {
			case 16:
				par->palette[regno] = ((red & 0xf800) >> 1) |
					((green & 0xf800) >> 6) |
					((blue & 0xf800) >> 11);
				break;
			case 32:
				par->palette[regno] = ((red & 0xff00) << 8) |
					((green & 0xff00)) |
					((blue & 0xff00) >> 8);
				break;
			}
		}
	}

	switch (info->var.bits_per_pixel) {
	case 8:
		/* "transparent" stuff is completely ignored. */
		riva_wclut(chip, regno, red >> 8, green >> 8, blue >> 8);
		break;
	case 16:
		if (info->var.green.length == 5) {
			for (i = 0; i < 8; i++) {
				riva_wclut(chip, regno*8+i, red >> 8,
					   green >> 8, blue >> 8);
			}
		} else {
			u8 r, g, b;

			if (regno < 32) {
				for (i = 0; i < 8; i++) {
					riva_wclut(chip, regno*8+i,
						   red >> 8, green >> 8,
						   blue >> 8);
				}
			}
			riva_rclut(chip, regno*4, &r, &g, &b);
			for (i = 0; i < 4; i++)
				riva_wclut(chip, regno*4+i, r,
					   green >> 8, b);
		}
		break;
	case 32:
		riva_wclut(chip, regno, red >> 8, green >> 8, blue >> 8);
		break;
	default:
		/* do nothing */
		break;
	}
	return 0;
}