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
typedef  int u32 ;
struct tridentfb_par {int dummy; } ;
struct TYPE_4__ {unsigned int len; } ;
struct TYPE_3__ {int bits_per_pixel; } ;
struct fb_info {scalar_t__ pseudo_palette; TYPE_2__ cmap; struct tridentfb_par* par; TYPE_1__ var; } ;

/* Variables and functions */
 int /*<<< orphan*/  VGA_PEL_D ; 
 int /*<<< orphan*/  VGA_PEL_IW ; 
 int /*<<< orphan*/  VGA_PEL_MSK ; 
 int /*<<< orphan*/  t_outb (struct tridentfb_par*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tridentfb_setcolreg(unsigned regno, unsigned red, unsigned green,
			       unsigned blue, unsigned transp,
			       struct fb_info *info)
{
	int bpp = info->var.bits_per_pixel;
	struct tridentfb_par *par = info->par;

	if (regno >= info->cmap.len)
		return 1;

	if (bpp == 8) {
		t_outb(par, 0xFF, VGA_PEL_MSK);
		t_outb(par, regno, VGA_PEL_IW);

		t_outb(par, red >> 10, VGA_PEL_D);
		t_outb(par, green >> 10, VGA_PEL_D);
		t_outb(par, blue >> 10, VGA_PEL_D);

	} else if (regno < 16) {
		if (bpp == 16) {	/* RGB 565 */
			u32 col;

			col = (red & 0xF800) | ((green & 0xFC00) >> 5) |
				((blue & 0xF800) >> 11);
			col |= col << 16;
			((u32 *)(info->pseudo_palette))[regno] = col;
		} else if (bpp == 32)		/* ARGB 8888 */
			((u32 *)info->pseudo_palette)[regno] =
				((transp & 0xFF00) << 16)	|
				((red & 0xFF00) << 8)		|
				((green & 0xFF00))		|
				((blue & 0xFF00) >> 8);
	}

	return 0;
}