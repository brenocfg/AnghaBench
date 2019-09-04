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
struct TYPE_3__ {int offset; } ;
struct TYPE_4__ {TYPE_1__ red; } ;
struct fb_info {scalar_t__ pseudo_palette; TYPE_2__ var; } ;

/* Variables and functions */
 scalar_t__ mmio_base ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static int asiliantfb_setcolreg(u_int regno, u_int red, u_int green, u_int blue,
			     u_int transp, struct fb_info *p)
{
	if (regno > 255)
		return 1;
	red >>= 8;
	green >>= 8;
	blue >>= 8;

        /* Set hardware palete */
	writeb(regno, mmio_base + 0x790);
	udelay(1);
	writeb(red, mmio_base + 0x791);
	writeb(green, mmio_base + 0x791);
	writeb(blue, mmio_base + 0x791);

	if (regno < 16) {
		switch(p->var.red.offset) {
		case 10: /* RGB 555 */
			((u32 *)(p->pseudo_palette))[regno] =
				((red & 0xf8) << 7) |
				((green & 0xf8) << 2) |
				((blue & 0xf8) >> 3);
			break;
		case 11: /* RGB 565 */
			((u32 *)(p->pseudo_palette))[regno] =
				((red & 0xf8) << 8) |
				((green & 0xfc) << 3) |
				((blue & 0xf8) >> 3);
			break;
		case 16: /* RGB 888 */
			((u32 *)(p->pseudo_palette))[regno] =
				(red << 16)  |
				(green << 8) |
				(blue);
			break;
		}
	}

	return 0;
}