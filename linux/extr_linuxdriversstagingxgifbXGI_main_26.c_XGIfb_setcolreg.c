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
typedef  unsigned int u32 ;
struct vb_device_info {int /*<<< orphan*/  Part5Port; int /*<<< orphan*/  P3c9; int /*<<< orphan*/  P3c8; } ;
struct xgifb_video_info {int /*<<< orphan*/  display2; struct vb_device_info dev_info; } ;
struct TYPE_2__ {int bits_per_pixel; } ;
struct fb_info {scalar_t__ pseudo_palette; TYPE_1__ var; struct xgifb_video_info* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  XGIFB_DISP_NONE ; 
 unsigned int XGIfb_get_cmap_len (TYPE_1__*) ; 
 int /*<<< orphan*/  outb (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int XGIfb_setcolreg(unsigned int regno, unsigned int red,
			   unsigned int green, unsigned int blue,
			   unsigned int transp, struct fb_info *info)
{
	struct xgifb_video_info *xgifb_info = info->par;
	struct vb_device_info *vb = &xgifb_info->dev_info;

	if (regno >= XGIfb_get_cmap_len(&info->var))
		return 1;

	switch (info->var.bits_per_pixel) {
	case 8:
		outb(regno, vb->P3c8);
		outb((red >> 10), vb->P3c9);
		outb((green >> 10), vb->P3c9);
		outb((blue >> 10), vb->P3c9);
		if (xgifb_info->display2 != XGIFB_DISP_NONE) {
			outb(regno, vb->Part5Port);
			outb((red >> 8), (vb->Part5Port + 1));
			outb((green >> 8), (vb->Part5Port + 1));
			outb((blue >> 8), (vb->Part5Port + 1));
		}
		break;
	case 16:
		((u32 *)(info->pseudo_palette))[regno] = ((red & 0xf800))
				| ((green & 0xfc00) >> 5) | ((blue & 0xf800)
				>> 11);
		break;
	case 32:
		red >>= 8;
		green >>= 8;
		blue >>= 8;
		((u32 *)(info->pseudo_palette))[regno] = (red << 16) | (green
				<< 8) | (blue);
		break;
	}
	return 0;
}