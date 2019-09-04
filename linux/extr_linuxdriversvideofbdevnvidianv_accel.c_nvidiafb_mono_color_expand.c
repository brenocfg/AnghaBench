#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct nvidia_par {int dummy; } ;
struct TYPE_2__ {int bits_per_pixel; } ;
struct fb_info {scalar_t__ pseudo_palette; TYPE_1__ var; struct nvidia_par* par; } ;
struct fb_image {int width; int height; int fg_color; int bg_color; int dy; int dx; scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVDmaKickoff (struct nvidia_par*) ; 
 int /*<<< orphan*/  NVDmaNext (struct nvidia_par*,int) ; 
 int /*<<< orphan*/  NVDmaStart (struct fb_info*,struct nvidia_par*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RECT_EXPAND_TWO_COLOR_CLIP ; 
 int /*<<< orphan*/  RECT_EXPAND_TWO_COLOR_DATA (int /*<<< orphan*/ ) ; 
 int RECT_EXPAND_TWO_COLOR_DATA_MAX_DWORDS ; 
 int /*<<< orphan*/  reverse_order (int*) ; 

__attribute__((used)) static void nvidiafb_mono_color_expand(struct fb_info *info,
				       const struct fb_image *image)
{
	struct nvidia_par *par = info->par;
	u32 fg, bg, mask = ~(~0 >> (32 - info->var.bits_per_pixel));
	u32 dsize, width, *data = (u32 *) image->data, tmp;
	int j, k = 0;

	width = (image->width + 31) & ~31;
	dsize = (width * image->height) >> 5;

	if (info->var.bits_per_pixel == 8) {
		fg = image->fg_color | mask;
		bg = image->bg_color | mask;
	} else {
		fg = ((u32 *) info->pseudo_palette)[image->fg_color] | mask;
		bg = ((u32 *) info->pseudo_palette)[image->bg_color] | mask;
	}

	NVDmaStart(info, par, RECT_EXPAND_TWO_COLOR_CLIP, 7);
	NVDmaNext(par, (image->dy << 16) | (image->dx & 0xffff));
	NVDmaNext(par, ((image->dy + image->height) << 16) |
		  ((image->dx + image->width) & 0xffff));
	NVDmaNext(par, bg);
	NVDmaNext(par, fg);
	NVDmaNext(par, (image->height << 16) | width);
	NVDmaNext(par, (image->height << 16) | width);
	NVDmaNext(par, (image->dy << 16) | (image->dx & 0xffff));

	while (dsize >= RECT_EXPAND_TWO_COLOR_DATA_MAX_DWORDS) {
		NVDmaStart(info, par, RECT_EXPAND_TWO_COLOR_DATA(0),
			   RECT_EXPAND_TWO_COLOR_DATA_MAX_DWORDS);

		for (j = RECT_EXPAND_TWO_COLOR_DATA_MAX_DWORDS; j--;) {
			tmp = data[k++];
			reverse_order(&tmp);
			NVDmaNext(par, tmp);
		}

		dsize -= RECT_EXPAND_TWO_COLOR_DATA_MAX_DWORDS;
	}

	if (dsize) {
		NVDmaStart(info, par, RECT_EXPAND_TWO_COLOR_DATA(0), dsize);

		for (j = dsize; j--;) {
			tmp = data[k++];
			reverse_order(&tmp);
			NVDmaNext(par, tmp);
		}
	}

	NVDmaKickoff(par);
}