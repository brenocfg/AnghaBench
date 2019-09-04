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
struct TYPE_3__ {int length; } ;
struct TYPE_4__ {int bits_per_pixel; TYPE_1__ green; int /*<<< orphan*/  nonstd; } ;
struct fb_info {scalar_t__ pseudo_palette; TYPE_2__ var; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  VGA_PEL_D ; 
 int /*<<< orphan*/  VGA_PEL_IW ; 
 int /*<<< orphan*/  VGA_PEL_MSK ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s3fb_setcolreg(u_int regno, u_int red, u_int green, u_int blue,
				u_int transp, struct fb_info *fb)
{
	switch (fb->var.bits_per_pixel) {
	case 0:
	case 4:
		if (regno >= 16)
			return -EINVAL;

		if ((fb->var.bits_per_pixel == 4) &&
		    (fb->var.nonstd == 0)) {
			outb(0xF0, VGA_PEL_MSK);
			outb(regno*16, VGA_PEL_IW);
		} else {
			outb(0x0F, VGA_PEL_MSK);
			outb(regno, VGA_PEL_IW);
		}
		outb(red >> 10, VGA_PEL_D);
		outb(green >> 10, VGA_PEL_D);
		outb(blue >> 10, VGA_PEL_D);
		break;
	case 8:
		if (regno >= 256)
			return -EINVAL;

		outb(0xFF, VGA_PEL_MSK);
		outb(regno, VGA_PEL_IW);
		outb(red >> 10, VGA_PEL_D);
		outb(green >> 10, VGA_PEL_D);
		outb(blue >> 10, VGA_PEL_D);
		break;
	case 16:
		if (regno >= 16)
			return 0;

		if (fb->var.green.length == 5)
			((u32*)fb->pseudo_palette)[regno] = ((red & 0xF800) >> 1) |
				((green & 0xF800) >> 6) | ((blue & 0xF800) >> 11);
		else if (fb->var.green.length == 6)
			((u32*)fb->pseudo_palette)[regno] = (red & 0xF800) |
				((green & 0xFC00) >> 5) | ((blue & 0xF800) >> 11);
		else return -EINVAL;
		break;
	case 24:
	case 32:
		if (regno >= 16)
			return 0;

		((u32*)fb->pseudo_palette)[regno] = ((red & 0xFF00) << 8) |
			(green & 0xFF00) | ((blue & 0xFF00) >> 8);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}