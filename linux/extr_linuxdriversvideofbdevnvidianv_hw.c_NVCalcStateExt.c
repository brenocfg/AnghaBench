#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nvidia_par {int Architecture; int Chipset; int CursorStart; int /*<<< orphan*/  PFB; int /*<<< orphan*/  PRAMDAC0; int /*<<< orphan*/  FlatPanel; scalar_t__ twoStagePLL; } ;
struct TYPE_3__ {int bpp; int width; int height; int arbitration0; int arbitration1; int cursor0; int cursor1; int cursor2; int pllsel; int config; int general; int repaint1; int control; int repaint0; int pixel; int /*<<< orphan*/  pll; int /*<<< orphan*/  pllB; } ;
typedef  TYPE_1__ RIVA_HW_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  CalcVClock (int,int*,int /*<<< orphan*/ *,struct nvidia_par*) ; 
 int /*<<< orphan*/  CalcVClock2Stage (int,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct nvidia_par*) ; 
 int FB_VMODE_DOUBLE ; 
#define  NV_ARCH_04 132 
#define  NV_ARCH_10 131 
#define  NV_ARCH_20 130 
#define  NV_ARCH_30 129 
#define  NV_ARCH_40 128 
 int NV_RD32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nForceUpdateArbitrationSettings (int,int,int*,int*,struct nvidia_par*) ; 
 int /*<<< orphan*/  nv10UpdateArbitrationSettings (int,int,int*,int*,struct nvidia_par*) ; 
 int /*<<< orphan*/  nv30UpdateArbitrationSettings (struct nvidia_par*,int*,int*) ; 
 int /*<<< orphan*/  nv4UpdateArbitrationSettings (int,int,int*,int*,struct nvidia_par*) ; 

void NVCalcStateExt(struct nvidia_par *par,
		    RIVA_HW_STATE * state,
		    int bpp,
		    int width,
		    int hDisplaySize, int height, int dotClock, int flags)
{
	int pixelDepth, VClk = 0;
	/*
	 * Save mode parameters.
	 */
	state->bpp = bpp;	/* this is not bitsPerPixel, it's 8,15,16,32 */
	state->width = width;
	state->height = height;
	/*
	 * Extended RIVA registers.
	 */
	pixelDepth = (bpp + 1) / 8;
	if (par->twoStagePLL)
		CalcVClock2Stage(dotClock, &VClk, &state->pll, &state->pllB,
				 par);
	else
		CalcVClock(dotClock, &VClk, &state->pll, par);

	switch (par->Architecture) {
	case NV_ARCH_04:
		nv4UpdateArbitrationSettings(VClk,
					     pixelDepth * 8,
					     &(state->arbitration0),
					     &(state->arbitration1), par);
		state->cursor0 = 0x00;
		state->cursor1 = 0xbC;
		if (flags & FB_VMODE_DOUBLE)
			state->cursor1 |= 2;
		state->cursor2 = 0x00000000;
		state->pllsel = 0x10000700;
		state->config = 0x00001114;
		state->general = bpp == 16 ? 0x00101100 : 0x00100100;
		state->repaint1 = hDisplaySize < 1280 ? 0x04 : 0x00;
		break;
	case NV_ARCH_40:
		if (!par->FlatPanel)
			state->control = NV_RD32(par->PRAMDAC0, 0x0580) &
				0xeffffeff;
		/* fallthrough */
	case NV_ARCH_10:
	case NV_ARCH_20:
	case NV_ARCH_30:
	default:
		if ((par->Chipset & 0xfff0) == 0x0240 ||
		    (par->Chipset & 0xfff0) == 0x03d0) {
			state->arbitration0 = 256;
			state->arbitration1 = 0x0480;
		} else if (((par->Chipset & 0xffff) == 0x01A0) ||
		    ((par->Chipset & 0xffff) == 0x01f0)) {
			nForceUpdateArbitrationSettings(VClk,
							pixelDepth * 8,
							&(state->arbitration0),
							&(state->arbitration1),
							par);
		} else if (par->Architecture < NV_ARCH_30) {
			nv10UpdateArbitrationSettings(VClk,
						      pixelDepth * 8,
						      &(state->arbitration0),
						      &(state->arbitration1),
						      par);
		} else {
			nv30UpdateArbitrationSettings(par,
						      &(state->arbitration0),
						      &(state->arbitration1));
		}

		state->cursor0 = 0x80 | (par->CursorStart >> 17);
		state->cursor1 = (par->CursorStart >> 11) << 2;
		state->cursor2 = par->CursorStart >> 24;
		if (flags & FB_VMODE_DOUBLE)
			state->cursor1 |= 2;
		state->pllsel = 0x10000700;
		state->config = NV_RD32(par->PFB, 0x00000200);
		state->general = bpp == 16 ? 0x00101100 : 0x00100100;
		state->repaint1 = hDisplaySize < 1280 ? 0x04 : 0x00;
		break;
	}

	if (bpp != 8)		/* DirectColor */
		state->general |= 0x00000030;

	state->repaint0 = (((width / 8) * pixelDepth) & 0x700) >> 3;
	state->pixel = (pixelDepth > 2) ? 3 : pixelDepth;
}