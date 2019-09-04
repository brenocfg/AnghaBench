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
typedef  int u_int ;
struct par_info {int* crtc; int pitch; int crtc_ofl; } ;
struct fb_var_screeninfo {int xres; int right_margin; int hsync_len; int left_margin; int yres; int lower_margin; int vsync_len; int upper_margin; int vmode; } ;
struct cfb_info {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EXT_CRT_VRTOFL_INTERLACE ; 
 int EXT_CRT_VRTOFL_LINECOMP10 ; 
 int FB_VMODE_INTERLACED ; 
 int FB_VMODE_MASK ; 

__attribute__((used)) static int
cyber2000fb_decode_crtc(struct par_info *hw, struct cfb_info *cfb,
			struct fb_var_screeninfo *var)
{
	u_int Htotal, Hblankend, Hsyncend;
	u_int Vtotal, Vdispend, Vblankstart, Vblankend, Vsyncstart, Vsyncend;
#define ENCODE_BIT(v, b1, m, b2) ((((v) >> (b1)) & (m)) << (b2))

	hw->crtc[13] = hw->pitch;
	hw->crtc[17] = 0xe3;
	hw->crtc[14] = 0;
	hw->crtc[8]  = 0;

	Htotal     = var->xres + var->right_margin +
		     var->hsync_len + var->left_margin;

	if (Htotal > 2080)
		return -EINVAL;

	hw->crtc[0] = (Htotal >> 3) - 5;
	hw->crtc[1] = (var->xres >> 3) - 1;
	hw->crtc[2] = var->xres >> 3;
	hw->crtc[4] = (var->xres + var->right_margin) >> 3;

	Hblankend   = (Htotal - 4 * 8) >> 3;

	hw->crtc[3] = ENCODE_BIT(Hblankend,  0, 0x1f,  0) |
		      ENCODE_BIT(1,          0, 0x01,  7);

	Hsyncend    = (var->xres + var->right_margin + var->hsync_len) >> 3;

	hw->crtc[5] = ENCODE_BIT(Hsyncend,   0, 0x1f,  0) |
		      ENCODE_BIT(Hblankend,  5, 0x01,  7);

	Vdispend    = var->yres - 1;
	Vsyncstart  = var->yres + var->lower_margin;
	Vsyncend    = var->yres + var->lower_margin + var->vsync_len;
	Vtotal      = var->yres + var->lower_margin + var->vsync_len +
		      var->upper_margin - 2;

	if (Vtotal > 2047)
		return -EINVAL;

	Vblankstart = var->yres + 6;
	Vblankend   = Vtotal - 10;

	hw->crtc[6]  = Vtotal;
	hw->crtc[7]  = ENCODE_BIT(Vtotal,     8, 0x01,  0) |
			ENCODE_BIT(Vdispend,   8, 0x01,  1) |
			ENCODE_BIT(Vsyncstart, 8, 0x01,  2) |
			ENCODE_BIT(Vblankstart, 8, 0x01,  3) |
			ENCODE_BIT(1,          0, 0x01,  4) |
			ENCODE_BIT(Vtotal,     9, 0x01,  5) |
			ENCODE_BIT(Vdispend,   9, 0x01,  6) |
			ENCODE_BIT(Vsyncstart, 9, 0x01,  7);
	hw->crtc[9]  = ENCODE_BIT(0,          0, 0x1f,  0) |
			ENCODE_BIT(Vblankstart, 9, 0x01,  5) |
			ENCODE_BIT(1,          0, 0x01,  6);
	hw->crtc[10] = Vsyncstart;
	hw->crtc[11] = ENCODE_BIT(Vsyncend,   0, 0x0f,  0) |
		       ENCODE_BIT(1,          0, 0x01,  7);
	hw->crtc[12] = Vdispend;
	hw->crtc[15] = Vblankstart;
	hw->crtc[16] = Vblankend;
	hw->crtc[18] = 0xff;

	/*
	 * overflow - graphics reg 0x11
	 * 0=VTOTAL:10 1=VDEND:10 2=VRSTART:10 3=VBSTART:10
	 * 4=LINECOMP:10 5-IVIDEO 6=FIXCNT
	 */
	hw->crtc_ofl =
		ENCODE_BIT(Vtotal, 10, 0x01, 0) |
		ENCODE_BIT(Vdispend, 10, 0x01, 1) |
		ENCODE_BIT(Vsyncstart, 10, 0x01, 2) |
		ENCODE_BIT(Vblankstart, 10, 0x01, 3) |
		EXT_CRT_VRTOFL_LINECOMP10;

	/* woody: set the interlaced bit... */
	/* FIXME: what about doublescan? */
	if ((var->vmode & FB_VMODE_MASK) == FB_VMODE_INTERLACED)
		hw->crtc_ofl |= EXT_CRT_VRTOFL_INTERLACE;

	return 0;
}