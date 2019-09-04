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
typedef  int u32 ;
struct TYPE_4__ {int bits_per_pixel; } ;
struct TYPE_3__ {int len; } ;
struct fb_info {scalar_t__ pseudo_palette; TYPE_2__ var; TYPE_1__ cmap; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  outb (int,int) ; 

__attribute__((used)) static int neofb_setcolreg(u_int regno, u_int red, u_int green, u_int blue,
			   u_int transp, struct fb_info *fb)
{
	if (regno >= fb->cmap.len || regno > 255)
		return -EINVAL;

	if (fb->var.bits_per_pixel <= 8) {
		outb(regno, 0x3c8);

		outb(red >> 10, 0x3c9);
		outb(green >> 10, 0x3c9);
		outb(blue >> 10, 0x3c9);
	} else if (regno < 16) {
		switch (fb->var.bits_per_pixel) {
		case 16:
			((u32 *) fb->pseudo_palette)[regno] =
				((red & 0xf800)) | ((green & 0xfc00) >> 5) |
				((blue & 0xf800) >> 11);
			break;
		case 24:
			((u32 *) fb->pseudo_palette)[regno] =
				((red & 0xff00) << 8) | ((green & 0xff00)) |
				((blue & 0xff00) >> 8);
			break;
#ifdef NO_32BIT_SUPPORT_YET
		case 32:
			((u32 *) fb->pseudo_palette)[regno] =
				((transp & 0xff00) << 16) | ((red & 0xff00) << 8) |
				((green & 0xff00)) | ((blue & 0xff00) >> 8);
			break;
#endif
		default:
			return 1;
		}
	}

	return 0;
}