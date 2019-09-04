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
struct tdfx_par {int max_pixclock; } ;
struct TYPE_4__ {int xres; int right_margin; int hsync_len; int left_margin; int bits_per_pixel; int vmode; int yres; int lower_margin; int vsync_len; int upper_margin; int yoffset; int xoffset; int /*<<< orphan*/  pixclock; } ;
struct TYPE_3__ {int line_length; int /*<<< orphan*/  visual; int /*<<< orphan*/  smem_len; } ;
struct fb_info {TYPE_2__ var; TYPE_1__ fix; struct tdfx_par* par; } ;
struct banshee_reg {int vidcfg; int screensize; int* crt; int* misc; int* gra; int* att; int* seq; int* ext; int vgainit0; int vgainit1; int cursc1; int stride; int startaddr; int miscinit0; int /*<<< orphan*/  vidpll; scalar_t__ cursc0; scalar_t__ cursloc; int /*<<< orphan*/  curspataddr; int /*<<< orphan*/  dacmode; } ;
typedef  int /*<<< orphan*/  reg ;

/* Variables and functions */
 int /*<<< orphan*/  DACMODE_2X ; 
 int /*<<< orphan*/  DPRINTK (char*,int,int,int) ; 
 int /*<<< orphan*/  FB_VISUAL_PSEUDOCOLOR ; 
 int /*<<< orphan*/  FB_VISUAL_TRUECOLOR ; 
 int FB_VMODE_DOUBLE ; 
 int FB_VMODE_INTERLACED ; 
 int FB_VMODE_MASK ; 
 int /*<<< orphan*/  MISCINIT0 ; 
 int PICOS2KHZ (int /*<<< orphan*/ ) ; 
 int VGAINIT0_8BIT_DAC ; 
 int VGAINIT0_ALT_READBACK ; 
 int VGAINIT0_EXTSHIFTOUT ; 
 int VGAINIT0_EXT_ENABLE ; 
 int VGAINIT0_WAKEUP_3C3 ; 
 int /*<<< orphan*/  VGAINIT1 ; 
 int VIDCFG_2X ; 
 int VIDCFG_CLUT_BYPASS ; 
 int VIDCFG_CURS_X11 ; 
 int VIDCFG_DESK_ENABLE ; 
 int VIDCFG_HALF_MODE ; 
 int VIDCFG_INTERLACE ; 
 int VIDCFG_PIXFMT_SHIFT ; 
 int VIDCFG_VIDPROC_ENABLE ; 
 int /*<<< orphan*/  do_calc_pll (int,int*) ; 
 int /*<<< orphan*/  do_write_regs (struct fb_info*,struct banshee_reg*) ; 
 scalar_t__ hwcursor ; 
 int /*<<< orphan*/  memset (struct banshee_reg*,int /*<<< orphan*/ ,int) ; 
 int tdfx_inl (struct tdfx_par*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tdfxfb_set_par(struct fb_info *info)
{
	struct tdfx_par *par = info->par;
	u32 hdispend = info->var.xres;
	u32 hsyncsta = hdispend + info->var.right_margin;
	u32 hsyncend = hsyncsta + info->var.hsync_len;
	u32 htotal   = hsyncend + info->var.left_margin;
	u32 hd, hs, he, ht, hbs, hbe;
	u32 vd, vs, ve, vt, vbs, vbe;
	struct banshee_reg reg;
	int fout, freq;
	u32 wd;
	u32 cpp = (info->var.bits_per_pixel + 7) >> 3;

	memset(&reg, 0, sizeof(reg));

	reg.vidcfg = VIDCFG_VIDPROC_ENABLE | VIDCFG_DESK_ENABLE |
		     VIDCFG_CURS_X11 |
		     ((cpp - 1) << VIDCFG_PIXFMT_SHIFT) |
		     (cpp != 1 ? VIDCFG_CLUT_BYPASS : 0);

	/* PLL settings */
	freq = PICOS2KHZ(info->var.pixclock);

	reg.vidcfg &= ~VIDCFG_2X;

	if (freq > par->max_pixclock / 2) {
		freq = freq > par->max_pixclock ? par->max_pixclock : freq;
		reg.dacmode |= DACMODE_2X;
		reg.vidcfg  |= VIDCFG_2X;
		hdispend >>= 1;
		hsyncsta >>= 1;
		hsyncend >>= 1;
		htotal   >>= 1;
	}

	wd = (hdispend >> 3) - 1;
	hd  = wd;
	hs  = (hsyncsta >> 3) - 1;
	he  = (hsyncend >> 3) - 1;
	ht  = (htotal >> 3) - 1;
	hbs = hd;
	hbe = ht;

	if ((info->var.vmode & FB_VMODE_MASK) == FB_VMODE_DOUBLE) {
		vd = (info->var.yres << 1) - 1;
		vs  = vd + (info->var.lower_margin << 1);
		ve  = vs + (info->var.vsync_len << 1);
		vt = ve + (info->var.upper_margin << 1) - 1;
		reg.screensize = info->var.xres | (info->var.yres << 13);
		reg.vidcfg |= VIDCFG_HALF_MODE;
		reg.crt[0x09] = 0x80;
	} else {
		vd = info->var.yres - 1;
		vs  = vd + info->var.lower_margin;
		ve  = vs + info->var.vsync_len;
		vt = ve + info->var.upper_margin - 1;
		reg.screensize = info->var.xres | (info->var.yres << 12);
		reg.vidcfg &= ~VIDCFG_HALF_MODE;
	}
	vbs = vd;
	vbe = vt;

	/* this is all pretty standard VGA register stuffing */
	reg.misc[0x00] = 0x0f |
			(info->var.xres < 400 ? 0xa0 :
			 info->var.xres < 480 ? 0x60 :
			 info->var.xres < 768 ? 0xe0 : 0x20);

	reg.gra[0x05] = 0x40;
	reg.gra[0x06] = 0x05;
	reg.gra[0x07] = 0x0f;
	reg.gra[0x08] = 0xff;

	reg.att[0x00] = 0x00;
	reg.att[0x01] = 0x01;
	reg.att[0x02] = 0x02;
	reg.att[0x03] = 0x03;
	reg.att[0x04] = 0x04;
	reg.att[0x05] = 0x05;
	reg.att[0x06] = 0x06;
	reg.att[0x07] = 0x07;
	reg.att[0x08] = 0x08;
	reg.att[0x09] = 0x09;
	reg.att[0x0a] = 0x0a;
	reg.att[0x0b] = 0x0b;
	reg.att[0x0c] = 0x0c;
	reg.att[0x0d] = 0x0d;
	reg.att[0x0e] = 0x0e;
	reg.att[0x0f] = 0x0f;
	reg.att[0x10] = 0x41;
	reg.att[0x12] = 0x0f;

	reg.seq[0x00] = 0x03;
	reg.seq[0x01] = 0x01; /* fixme: clkdiv2? */
	reg.seq[0x02] = 0x0f;
	reg.seq[0x03] = 0x00;
	reg.seq[0x04] = 0x0e;

	reg.crt[0x00] = ht - 4;
	reg.crt[0x01] = hd;
	reg.crt[0x02] = hbs;
	reg.crt[0x03] = 0x80 | (hbe & 0x1f);
	reg.crt[0x04] = hs;
	reg.crt[0x05] = ((hbe & 0x20) << 2) | (he & 0x1f);
	reg.crt[0x06] = vt;
	reg.crt[0x07] = ((vs & 0x200) >> 2) |
			((vd & 0x200) >> 3) |
			((vt & 0x200) >> 4) | 0x10 |
			((vbs & 0x100) >> 5) |
			((vs & 0x100) >> 6) |
			((vd & 0x100) >> 7) |
			((vt & 0x100) >> 8);
	reg.crt[0x09] |= 0x40 | ((vbs & 0x200) >> 4);
	reg.crt[0x10] = vs;
	reg.crt[0x11] = (ve & 0x0f) | 0x20;
	reg.crt[0x12] = vd;
	reg.crt[0x13] = wd;
	reg.crt[0x15] = vbs;
	reg.crt[0x16] = vbe + 1;
	reg.crt[0x17] = 0xc3;
	reg.crt[0x18] = 0xff;

	/* Banshee's nonvga stuff */
	reg.ext[0x00] = (((ht & 0x100) >> 8) |
			((hd & 0x100) >> 6) |
			((hbs & 0x100) >> 4) |
			((hbe & 0x40) >> 1) |
			((hs & 0x100) >> 2) |
			((he & 0x20) << 2));
	reg.ext[0x01] = (((vt & 0x400) >> 10) |
			((vd & 0x400) >> 8) |
			((vbs & 0x400) >> 6) |
			((vbe & 0x400) >> 4));

	reg.vgainit0 =	VGAINIT0_8BIT_DAC     |
			VGAINIT0_EXT_ENABLE   |
			VGAINIT0_WAKEUP_3C3   |
			VGAINIT0_ALT_READBACK |
			VGAINIT0_EXTSHIFTOUT;
	reg.vgainit1 = tdfx_inl(par, VGAINIT1) & 0x1fffff;

	if (hwcursor)
		reg.curspataddr = info->fix.smem_len;

	reg.cursloc   = 0;

	reg.cursc0    = 0;
	reg.cursc1    = 0xffffff;

	reg.stride    = info->var.xres * cpp;
	reg.startaddr = info->var.yoffset * reg.stride
			+ info->var.xoffset * cpp;

	reg.vidpll = do_calc_pll(freq, &fout);
#if 0
	reg.mempll = do_calc_pll(..., &fout);
	reg.gfxpll = do_calc_pll(..., &fout);
#endif

	if ((info->var.vmode & FB_VMODE_MASK) == FB_VMODE_INTERLACED)
		reg.vidcfg |= VIDCFG_INTERLACE;
	reg.miscinit0 = tdfx_inl(par, MISCINIT0);

#if defined(__BIG_ENDIAN)
	switch (info->var.bits_per_pixel) {
	case 8:
	case 24:
		reg.miscinit0 &= ~(1 << 30);
		reg.miscinit0 &= ~(1 << 31);
		break;
	case 16:
		reg.miscinit0 |= (1 << 30);
		reg.miscinit0 |= (1 << 31);
		break;
	case 32:
		reg.miscinit0 |= (1 << 30);
		reg.miscinit0 &= ~(1 << 31);
		break;
	}
#endif
	do_write_regs(info, &reg);

	/* Now change fb_fix_screeninfo according to changes in par */
	info->fix.line_length = reg.stride;
	info->fix.visual = (info->var.bits_per_pixel == 8)
				? FB_VISUAL_PSEUDOCOLOR
				: FB_VISUAL_TRUECOLOR;
	DPRINTK("Graphics mode is now set at %dx%d depth %d\n",
		info->var.xres, info->var.yres, info->var.bits_per_pixel);
	return 0;
}