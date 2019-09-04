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
struct TYPE_3__ {int length; } ;
struct TYPE_4__ {int bits_per_pixel; TYPE_1__ green; int /*<<< orphan*/  yres; int /*<<< orphan*/  xres; } ;
struct fb_info {TYPE_2__ var; } ;

/* Variables and functions */
 unsigned long FMsk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GBBASE ; 
 int /*<<< orphan*/  GDRCTRL ; 
 int /*<<< orphan*/  GPLUT ; 
 int /*<<< orphan*/  GSCADR ; 
 unsigned long GSCADR_STR_EN ; 
 int /*<<< orphan*/  GSCTRL ; 
 unsigned long GSCTRL_GAMMA_EN ; 
 unsigned long GSCTRL_GPIXFMT_ARGB1555 ; 
 unsigned long GSCTRL_GPIXFMT_ARGB8888 ; 
 unsigned long GSCTRL_GPIXFMT_RGB565 ; 
 unsigned long GSCTRL_GPIXFMT_RGB888 ; 
 unsigned long Gscadr_Gbase_Adr (int) ; 
 unsigned long Gsctrl_Height (int /*<<< orphan*/ ) ; 
 unsigned long Gsctrl_Width (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VSCADR ; 
 int /*<<< orphan*/  VSCADR_BLEND_M ; 
 unsigned long VSCADR_BLEND_NONE ; 
 int /*<<< orphan*/  VSCADR_BLEND_POS ; 
 unsigned long VSCADR_BLEND_VID ; 
 unsigned long readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_reg_dly (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setup_graphics(struct fb_info *fbi)
{
	unsigned long gsctrl;
	unsigned long vscadr;

	gsctrl = GSCTRL_GAMMA_EN | Gsctrl_Width(fbi->var.xres) |
		Gsctrl_Height(fbi->var.yres);
	switch (fbi->var.bits_per_pixel) {
	case 16:
		if (fbi->var.green.length == 5)
			gsctrl |= GSCTRL_GPIXFMT_ARGB1555;
		else
			gsctrl |= GSCTRL_GPIXFMT_RGB565;
		break;
	case 24:
		gsctrl |= GSCTRL_GPIXFMT_RGB888;
		break;
	case 32:
		gsctrl |= GSCTRL_GPIXFMT_ARGB8888;
		break;
	}

	write_reg_dly(gsctrl, GSCTRL);
	write_reg_dly(0x00000000, GBBASE);
	write_reg_dly(0x00ffffff, GDRCTRL);
	write_reg_dly((GSCADR_STR_EN | Gscadr_Gbase_Adr(0x6000)), GSCADR);
	write_reg_dly(0x00000000, GPLUT);

	vscadr = readl(VSCADR);
	vscadr &= ~(FMsk(VSCADR_BLEND_POS) | FMsk(VSCADR_BLEND_M));
	vscadr |= VSCADR_BLEND_VID | VSCADR_BLEND_NONE;
	write_reg_dly(vscadr, VSCADR);
}