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
typedef  int u32 ;
struct neofb_par {scalar_t__ mmio_vbase; TYPE_4__* neo2200; } ;
struct TYPE_7__ {int line_length; } ;
struct TYPE_6__ {int bits_per_pixel; } ;
struct TYPE_5__ {int scan_align; int buf_align; } ;
struct fb_info {TYPE_3__ fix; TYPE_2__ var; scalar_t__ pseudo_palette; TYPE_1__ pixmap; struct neofb_par* par; } ;
struct fb_image {int width; int depth; int height; int fg_color; int bg_color; int dx; int dy; int /*<<< orphan*/  data; } ;
struct TYPE_8__ {int /*<<< orphan*/  xyExt; int /*<<< orphan*/  dstStart; int /*<<< orphan*/  srcStart; int /*<<< orphan*/  bltCntl; int /*<<< orphan*/  bgColor; int /*<<< orphan*/  fgColor; } ;

/* Variables and functions */
 int NEO_BC0_SRC_MONO ; 
 int NEO_BC0_SYS_TO_VID ; 
 int NEO_BC3_SKIP_MAPPING ; 
 int /*<<< orphan*/  cfb_imageblit (struct fb_info*,struct fb_image const*) ; 
 int /*<<< orphan*/  memcpy_toio (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  neo2200_sync (struct fb_info*) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
neo2200_imageblit(struct fb_info *info, const struct fb_image *image)
{
	struct neofb_par *par = info->par;
	int s_pitch = (image->width * image->depth + 7) >> 3;
	int scan_align = info->pixmap.scan_align - 1;
	int buf_align = info->pixmap.buf_align - 1;
	int bltCntl_flags, d_pitch, data_len;

	// The data is padded for the hardware
	d_pitch = (s_pitch + scan_align) & ~scan_align;
	data_len = ((d_pitch * image->height) + buf_align) & ~buf_align;

	neo2200_sync(info);

	if (image->depth == 1) {
		if (info->var.bits_per_pixel == 24 && image->width < 16) {
			/* FIXME. There is a bug with accelerated color-expanded
			 * transfers in 24 bit mode if the image being transferred
			 * is less than 16 bits wide. This is due to insufficient
			 * padding when writing the image. We need to adjust
			 * struct fb_pixmap. Not yet done. */
			cfb_imageblit(info, image);
			return;
		}
		bltCntl_flags = NEO_BC0_SRC_MONO;
	} else if (image->depth == info->var.bits_per_pixel) {
		bltCntl_flags = 0;
	} else {
		/* We don't currently support hardware acceleration if image
		 * depth is different from display */
		cfb_imageblit(info, image);
		return;
	}

	switch (info->var.bits_per_pixel) {
	case 8:
		writel(image->fg_color, &par->neo2200->fgColor);
		writel(image->bg_color, &par->neo2200->bgColor);
		break;
	case 16:
	case 24:
		writel(((u32 *) (info->pseudo_palette))[image->fg_color],
		       &par->neo2200->fgColor);
		writel(((u32 *) (info->pseudo_palette))[image->bg_color],
		       &par->neo2200->bgColor);
		break;
	}

	writel(NEO_BC0_SYS_TO_VID |
		NEO_BC3_SKIP_MAPPING | bltCntl_flags |
		// NEO_BC3_DST_XY_ADDR |
		0x0c0000, &par->neo2200->bltCntl);

	writel(0, &par->neo2200->srcStart);
//      par->neo2200->dstStart = (image->dy << 16) | (image->dx & 0xffff);
	writel(((image->dx & 0xffff) * (info->var.bits_per_pixel >> 3) +
		image->dy * info->fix.line_length), &par->neo2200->dstStart);
	writel((image->height << 16) | (image->width & 0xffff),
	       &par->neo2200->xyExt);

	memcpy_toio(par->mmio_vbase + 0x100000, image->data, data_len);
}