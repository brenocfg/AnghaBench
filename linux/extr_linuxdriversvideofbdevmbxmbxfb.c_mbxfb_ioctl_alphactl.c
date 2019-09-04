#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mbxfb_alphaCtl {int overlay_colorkey_mode; int overlay_blend_mode; int graphics_colorkey_mode; int graphics_blend_mode; int /*<<< orphan*/  graphics_colorkey_mask; int /*<<< orphan*/  overlay_colorkey_mask; int /*<<< orphan*/  graphics_colorkey; int /*<<< orphan*/  graphics_global_alpha; int /*<<< orphan*/  overlay_colorkey; int /*<<< orphan*/  overlay_global_alpha; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long FMsk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GBBASE ; 
 int /*<<< orphan*/  GDRCTRL ; 
 int /*<<< orphan*/  GDRCTRL_COLKEYM ; 
 int /*<<< orphan*/  GSCADR ; 
 unsigned long GSCADR_BLEND_GLOB ; 
 int /*<<< orphan*/  GSCADR_BLEND_M ; 
 unsigned long GSCADR_BLEND_NONE ; 
 unsigned long GSCADR_BLEND_PIX ; 
 unsigned long GSCADR_COLKEYSRC ; 
 unsigned long GSCADR_COLKEY_EN ; 
 unsigned long Gbbase_Colkey (int /*<<< orphan*/ ) ; 
 unsigned long Gbbase_Glalpha (int /*<<< orphan*/ ) ; 
 unsigned long Gdrctrl_Colkeym (int /*<<< orphan*/ ) ; 
#define  MBXFB_ALPHABLEND_GLOBAL 133 
#define  MBXFB_ALPHABLEND_NONE 132 
#define  MBXFB_ALPHABLEND_PIXEL 131 
#define  MBXFB_COLORKEY_CURRENT 130 
#define  MBXFB_COLORKEY_DISABLED 129 
#define  MBXFB_COLORKEY_PREVIOUS 128 
 int /*<<< orphan*/  VBBASE ; 
 int /*<<< orphan*/  VCMSK ; 
 int /*<<< orphan*/  VCMSK_COLKEY_M ; 
 int /*<<< orphan*/  VSCADR ; 
 unsigned long VSCADR_BLEND_GLOB ; 
 int /*<<< orphan*/  VSCADR_BLEND_M ; 
 unsigned long VSCADR_BLEND_NONE ; 
 unsigned long VSCADR_BLEND_PIX ; 
 unsigned long VSCADR_COLKEYSRC ; 
 unsigned long VSCADR_COLKEY_EN ; 
 unsigned long Vbbase_Colkey (int /*<<< orphan*/ ) ; 
 unsigned long Vbbase_Glalpha (int /*<<< orphan*/ ) ; 
 unsigned long Vcmsk_colkey_m (int /*<<< orphan*/ ) ; 
 unsigned long readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_reg_dly (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mbxfb_ioctl_alphactl(struct mbxfb_alphaCtl *alpha)
{
	unsigned long vscadr, vbbase, vcmsk;
	unsigned long gscadr, gbbase, gdrctrl;

	vbbase = Vbbase_Glalpha(alpha->overlay_global_alpha) |
				Vbbase_Colkey(alpha->overlay_colorkey);

	gbbase = Gbbase_Glalpha(alpha->graphics_global_alpha) |
				Gbbase_Colkey(alpha->graphics_colorkey);

	vcmsk = readl(VCMSK);
	vcmsk &= ~(FMsk(VCMSK_COLKEY_M));
	vcmsk |= Vcmsk_colkey_m(alpha->overlay_colorkey_mask);

	gdrctrl = readl(GDRCTRL);
	gdrctrl &= ~(FMsk(GDRCTRL_COLKEYM));
	gdrctrl |= Gdrctrl_Colkeym(alpha->graphics_colorkey_mask);

	vscadr = readl(VSCADR);
	vscadr &= ~(FMsk(VSCADR_BLEND_M) | VSCADR_COLKEYSRC | VSCADR_COLKEY_EN);

	gscadr = readl(GSCADR);
	gscadr &= ~(FMsk(GSCADR_BLEND_M) | GSCADR_COLKEY_EN | GSCADR_COLKEYSRC);

	switch (alpha->overlay_colorkey_mode) {
	case MBXFB_COLORKEY_DISABLED:
		break;
	case MBXFB_COLORKEY_PREVIOUS:
		vscadr |= VSCADR_COLKEY_EN;
		break;
	case MBXFB_COLORKEY_CURRENT:
		vscadr |= VSCADR_COLKEY_EN | VSCADR_COLKEYSRC;
		break;
	default:
		return -EINVAL;
	}

	switch (alpha->overlay_blend_mode) {
	case MBXFB_ALPHABLEND_NONE:
		vscadr |= VSCADR_BLEND_NONE;
		break;
	case MBXFB_ALPHABLEND_GLOBAL:
		vscadr |= VSCADR_BLEND_GLOB;
		break;
	case MBXFB_ALPHABLEND_PIXEL:
		vscadr |= VSCADR_BLEND_PIX;
		break;
	default:
		return -EINVAL;
	}

	switch (alpha->graphics_colorkey_mode) {
	case MBXFB_COLORKEY_DISABLED:
		break;
	case MBXFB_COLORKEY_PREVIOUS:
		gscadr |= GSCADR_COLKEY_EN;
		break;
	case MBXFB_COLORKEY_CURRENT:
		gscadr |= GSCADR_COLKEY_EN | GSCADR_COLKEYSRC;
		break;
	default:
		return -EINVAL;
	}

	switch (alpha->graphics_blend_mode) {
	case MBXFB_ALPHABLEND_NONE:
		gscadr |= GSCADR_BLEND_NONE;
		break;
	case MBXFB_ALPHABLEND_GLOBAL:
		gscadr |= GSCADR_BLEND_GLOB;
		break;
	case MBXFB_ALPHABLEND_PIXEL:
		gscadr |= GSCADR_BLEND_PIX;
		break;
	default:
		return -EINVAL;
	}

	write_reg_dly(vbbase, VBBASE);
	write_reg_dly(gbbase, GBBASE);
	write_reg_dly(vcmsk, VCMSK);
	write_reg_dly(gdrctrl, GDRCTRL);
	write_reg_dly(gscadr, GSCADR);
	write_reg_dly(vscadr, VSCADR);

	return 0;
}