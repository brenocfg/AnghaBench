#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct vga16fb_par {int pel_msk; int* crtc; int vss; int misc; int mode; scalar_t__ isVGA; } ;
struct TYPE_8__ {scalar_t__ length; scalar_t__ offset; } ;
struct TYPE_7__ {int length; scalar_t__ offset; } ;
struct TYPE_6__ {int length; scalar_t__ offset; } ;
struct TYPE_5__ {int length; scalar_t__ offset; } ;
struct fb_var_screeninfo {int bits_per_pixel; int xres; int xres_virtual; int xoffset; int left_margin; int right_margin; int hsync_len; int yres; int lower_margin; int vsync_len; int upper_margin; int yres_virtual; int yoffset; int vmode; int sync; int height; int width; scalar_t__ accel_flags; int /*<<< orphan*/  activate; TYPE_4__ transp; TYPE_3__ blue; TYPE_2__ green; TYPE_1__ red; int /*<<< orphan*/  pixclock; scalar_t__ nonstd; } ;
struct fb_info {struct vga16fb_par* par; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FAIL (char*) ; 
 int /*<<< orphan*/  FB_ACTIVATE_NOW ; 
 int FB_SYNC_HOR_HIGH_ACT ; 
 int FB_SYNC_VERT_HIGH_ACT ; 
 int FB_VMODE_DOUBLE ; 
 int MODE_8BPP ; 
 int MODE_CFB ; 
 int MODE_SKIP4 ; 
 int MODE_TEXT ; 
 size_t VGA_CRTC_CURSOR_END ; 
 size_t VGA_CRTC_CURSOR_HI ; 
 size_t VGA_CRTC_CURSOR_LO ; 
 size_t VGA_CRTC_CURSOR_START ; 
 size_t VGA_CRTC_H_BLANK_END ; 
 size_t VGA_CRTC_H_BLANK_START ; 
 size_t VGA_CRTC_H_DISP ; 
 size_t VGA_CRTC_H_SYNC_END ; 
 size_t VGA_CRTC_H_SYNC_START ; 
 size_t VGA_CRTC_H_TOTAL ; 
 size_t VGA_CRTC_LINE_COMPARE ; 
 size_t VGA_CRTC_MAX_SCAN ; 
 size_t VGA_CRTC_MODE ; 
 size_t VGA_CRTC_OFFSET ; 
 size_t VGA_CRTC_OVERFLOW ; 
 size_t VGA_CRTC_PRESET_ROW ; 
 size_t VGA_CRTC_START_HI ; 
 size_t VGA_CRTC_START_LO ; 
 size_t VGA_CRTC_UNDERLINE ; 
 size_t VGA_CRTC_V_BLANK_END ; 
 size_t VGA_CRTC_V_BLANK_START ; 
 size_t VGA_CRTC_V_DISP_END ; 
 size_t VGA_CRTC_V_SYNC_END ; 
 size_t VGA_CRTC_V_SYNC_START ; 
 size_t VGA_CRTC_V_TOTAL ; 
 int /*<<< orphan*/  vga16fb_clock_chip (struct vga16fb_par*,int /*<<< orphan*/ ,struct fb_info*,int,int) ; 

__attribute__((used)) static int vga16fb_check_var(struct fb_var_screeninfo *var,
			     struct fb_info *info)
{
	struct vga16fb_par *par = info->par;
	u32 xres, right, hslen, left, xtotal;
	u32 yres, lower, vslen, upper, ytotal;
	u32 vxres, xoffset, vyres, yoffset;
	u32 pos;
	u8 r7, rMode;
	int shift;
	int mode;
	u32 maxmem;

	par->pel_msk = 0xFF;

	if (var->bits_per_pixel == 4) {
		if (var->nonstd) {
			if (!par->isVGA)
				return -EINVAL;
			shift = 3;
			mode = MODE_SKIP4 | MODE_CFB;
			maxmem = 16384;
			par->pel_msk = 0x0F;
		} else {
			shift = 3;
			mode = 0;
			maxmem = 65536;
		}
	} else if (var->bits_per_pixel == 8) {
		if (!par->isVGA)
			return -EINVAL;	/* no support on EGA */
		shift = 2;
		if (var->nonstd) {
			mode = MODE_8BPP | MODE_CFB;
			maxmem = 65536;
		} else {
			mode = MODE_SKIP4 | MODE_8BPP | MODE_CFB;
			maxmem = 16384;
		}
	} else
		return -EINVAL;

	xres = (var->xres + 7) & ~7;
	vxres = (var->xres_virtual + 0xF) & ~0xF;
	xoffset = (var->xoffset + 7) & ~7;
	left = (var->left_margin + 7) & ~7;
	right = (var->right_margin + 7) & ~7;
	hslen = (var->hsync_len + 7) & ~7;

	if (vxres < xres)
		vxres = xres;
	if (xres + xoffset > vxres)
		xoffset = vxres - xres;

	var->xres = xres;
	var->right_margin = right;
	var->hsync_len = hslen;
	var->left_margin = left;
	var->xres_virtual = vxres;
	var->xoffset = xoffset;

	xres >>= shift;
	right >>= shift;
	hslen >>= shift;
	left >>= shift;
	vxres >>= shift;
	xtotal = xres + right + hslen + left;
	if (xtotal >= 256)
		FAIL("xtotal too big");
	if (hslen > 32)
		FAIL("hslen too big");
	if (right + hslen + left > 64)
		FAIL("hblank too big");
	par->crtc[VGA_CRTC_H_TOTAL] = xtotal - 5;
	par->crtc[VGA_CRTC_H_BLANK_START] = xres - 1;
	par->crtc[VGA_CRTC_H_DISP] = xres - 1;
	pos = xres + right;
	par->crtc[VGA_CRTC_H_SYNC_START] = pos;
	pos += hslen;
	par->crtc[VGA_CRTC_H_SYNC_END] = pos & 0x1F;
	pos += left - 2; /* blank_end + 2 <= total + 5 */
	par->crtc[VGA_CRTC_H_BLANK_END] = (pos & 0x1F) | 0x80;
	if (pos & 0x20)
		par->crtc[VGA_CRTC_H_SYNC_END] |= 0x80;

	yres = var->yres;
	lower = var->lower_margin;
	vslen = var->vsync_len;
	upper = var->upper_margin;
	vyres = var->yres_virtual;
	yoffset = var->yoffset;

	if (yres > vyres)
		vyres = yres;
	if (vxres * vyres > maxmem) {
		vyres = maxmem / vxres;
		if (vyres < yres)
			return -ENOMEM;
	}
	if (yoffset + yres > vyres)
		yoffset = vyres - yres;
	var->yres = yres;
	var->lower_margin = lower;
	var->vsync_len = vslen;
	var->upper_margin = upper;
	var->yres_virtual = vyres;
	var->yoffset = yoffset;

	if (var->vmode & FB_VMODE_DOUBLE) {
		yres <<= 1;
		lower <<= 1;
		vslen <<= 1;
		upper <<= 1;
	}
	ytotal = yres + lower + vslen + upper;
	if (ytotal > 1024) {
		ytotal >>= 1;
		yres >>= 1;
		lower >>= 1;
		vslen >>= 1;
		upper >>= 1;
		rMode = 0x04;
	} else
		rMode = 0x00;
	if (ytotal > 1024)
		FAIL("ytotal too big");
	if (vslen > 16)
		FAIL("vslen too big");
	par->crtc[VGA_CRTC_V_TOTAL] = ytotal - 2;
	r7 = 0x10;	/* disable linecompare */
	if (ytotal & 0x100) r7 |= 0x01;
	if (ytotal & 0x200) r7 |= 0x20;
	par->crtc[VGA_CRTC_PRESET_ROW] = 0;
	par->crtc[VGA_CRTC_MAX_SCAN] = 0x40;	/* 1 scanline, no linecmp */
	if (var->vmode & FB_VMODE_DOUBLE)
		par->crtc[VGA_CRTC_MAX_SCAN] |= 0x80;
	par->crtc[VGA_CRTC_CURSOR_START] = 0x20;
	par->crtc[VGA_CRTC_CURSOR_END]   = 0x00;
	if ((mode & (MODE_CFB | MODE_8BPP)) == MODE_CFB)
		xoffset--;
	pos = yoffset * vxres + (xoffset >> shift);
	par->crtc[VGA_CRTC_START_HI]     = pos >> 8;
	par->crtc[VGA_CRTC_START_LO]     = pos & 0xFF;
	par->crtc[VGA_CRTC_CURSOR_HI]    = 0x00;
	par->crtc[VGA_CRTC_CURSOR_LO]    = 0x00;
	pos = yres - 1;
	par->crtc[VGA_CRTC_V_DISP_END] = pos & 0xFF;
	par->crtc[VGA_CRTC_V_BLANK_START] = pos & 0xFF;
	if (pos & 0x100)
		r7 |= 0x0A;	/* 0x02 -> DISP_END, 0x08 -> BLANK_START */
	if (pos & 0x200) {
		r7 |= 0x40;	/* 0x40 -> DISP_END */
		par->crtc[VGA_CRTC_MAX_SCAN] |= 0x20; /* BLANK_START */
	}
	pos += lower;
	par->crtc[VGA_CRTC_V_SYNC_START] = pos & 0xFF;
	if (pos & 0x100)
		r7 |= 0x04;
	if (pos & 0x200)
		r7 |= 0x80;
	pos += vslen;
	par->crtc[VGA_CRTC_V_SYNC_END] = (pos & 0x0F) & ~0x10; /* disabled IRQ */
	pos += upper - 1; /* blank_end + 1 <= ytotal + 2 */
	par->crtc[VGA_CRTC_V_BLANK_END] = pos & 0xFF; /* 0x7F for original VGA,
                     but some SVGA chips requires all 8 bits to set */
	if (vxres >= 512)
		FAIL("vxres too long");
	par->crtc[VGA_CRTC_OFFSET] = vxres >> 1;
	if (mode & MODE_SKIP4)
		par->crtc[VGA_CRTC_UNDERLINE] = 0x5F;	/* 256, cfb8 */
	else
		par->crtc[VGA_CRTC_UNDERLINE] = 0x1F;	/* 16, vgap */
	par->crtc[VGA_CRTC_MODE] = rMode | ((mode & MODE_TEXT) ? 0xA3 : 0xE3);
	par->crtc[VGA_CRTC_LINE_COMPARE] = 0xFF;
	par->crtc[VGA_CRTC_OVERFLOW] = r7;

	par->vss = 0x00;	/* 3DA */

	par->misc = 0xE3;	/* enable CPU, ports 0x3Dx, positive sync */
	if (var->sync & FB_SYNC_HOR_HIGH_ACT)
		par->misc &= ~0x40;
	if (var->sync & FB_SYNC_VERT_HIGH_ACT)
		par->misc &= ~0x80;
	
	par->mode = mode;

	if (mode & MODE_8BPP)
		/* pixel clock == vga clock / 2 */
		vga16fb_clock_chip(par, var->pixclock, info, 1, 2);
	else
		/* pixel clock == vga clock */
		vga16fb_clock_chip(par, var->pixclock, info, 1, 1);
	
	var->red.offset = var->green.offset = var->blue.offset = 
	var->transp.offset = 0;
	var->red.length = var->green.length = var->blue.length =
		(par->isVGA) ? 6 : 2;
	var->transp.length = 0;
	var->activate = FB_ACTIVATE_NOW;
	var->height = -1;
	var->width = -1;
	var->accel_flags = 0;
	return 0;
}