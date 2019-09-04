#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct imstt_regvals {int pitch; int hes; int heb; int hsb; int ht; int ves; int veb; int vsb; int vt; int vil; } ;
struct imstt_par {scalar_t__ ramdac; int /*<<< orphan*/  dc_regs; struct imstt_regvals init; } ;
struct TYPE_2__ {int smem_len; } ;
struct fb_info {TYPE_1__ fix; struct imstt_par* par; } ;
typedef  int __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  CMR ; 
 int /*<<< orphan*/  HCIV ; 
 int /*<<< orphan*/  HEB ; 
 int /*<<< orphan*/  HES ; 
 int /*<<< orphan*/  HRIR ; 
 int /*<<< orphan*/  HSB ; 
 int /*<<< orphan*/  HT ; 
 scalar_t__ IBM ; 
 int /*<<< orphan*/  RRCIV ; 
 int /*<<< orphan*/  RRCR ; 
 int /*<<< orphan*/  RRSC ; 
 int /*<<< orphan*/  SCR ; 
 int /*<<< orphan*/  SPR ; 
 int /*<<< orphan*/  SRGCTL ; 
 int /*<<< orphan*/  STGCTL ; 
 int /*<<< orphan*/  TCDR ; 
 scalar_t__ TVP ; 
 int /*<<< orphan*/  VCIV ; 
 int /*<<< orphan*/  VEB ; 
 int /*<<< orphan*/  VES ; 
 int /*<<< orphan*/  VIL ; 
 int /*<<< orphan*/  VSB ; 
 int /*<<< orphan*/  VT ; 
 int /*<<< orphan*/  set_imstt_regvals_ibm (struct imstt_par*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_imstt_regvals_tvp (struct imstt_par*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_reg_le32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
set_imstt_regvals (struct fb_info *info, u_int bpp)
{
	struct imstt_par *par = info->par;
	struct imstt_regvals *init = &par->init;
	__u32 ctl, pitch, byteswap, scr;

	if (par->ramdac == IBM)
		set_imstt_regvals_ibm(par, bpp);
	else
		set_imstt_regvals_tvp(par, bpp);

  /*
   * From what I (jsk) can gather poking around with MacsBug,
   * bits 8 and 9 in the SCR register control endianness
   * correction (byte swapping).  These bits must be set according
   * to the color depth as follows:
   *     Color depth    Bit 9   Bit 8
   *     ==========     =====   =====
   *        8bpp          0       0
   *       16bpp          0       1
   *       32bpp          1       1
   */
	switch (bpp) {
		default:
		case 8:
			ctl = 0x17b1;
			pitch = init->pitch >> 2;
			byteswap = 0x000;
			break;
		case 16:
			ctl = 0x17b3;
			pitch = init->pitch >> 1;
			byteswap = 0x100;
			break;
		case 24:
			ctl = 0x17b9;
			pitch = init->pitch - (init->pitch >> 2);
			byteswap = 0x200;
			break;
		case 32:
			ctl = 0x17b5;
			pitch = init->pitch;
			byteswap = 0x300;
			break;
	}
	if (par->ramdac == TVP)
		ctl -= 0x30;

	write_reg_le32(par->dc_regs, HES, init->hes);
	write_reg_le32(par->dc_regs, HEB, init->heb);
	write_reg_le32(par->dc_regs, HSB, init->hsb);
	write_reg_le32(par->dc_regs, HT, init->ht);
	write_reg_le32(par->dc_regs, VES, init->ves);
	write_reg_le32(par->dc_regs, VEB, init->veb);
	write_reg_le32(par->dc_regs, VSB, init->vsb);
	write_reg_le32(par->dc_regs, VT, init->vt);
	write_reg_le32(par->dc_regs, VIL, init->vil);
	write_reg_le32(par->dc_regs, HCIV, 1);
	write_reg_le32(par->dc_regs, VCIV, 1);
	write_reg_le32(par->dc_regs, TCDR, 4);
	write_reg_le32(par->dc_regs, RRCIV, 1);
	write_reg_le32(par->dc_regs, RRSC, 0x980);
	write_reg_le32(par->dc_regs, RRCR, 0x11);

	if (par->ramdac == IBM) {
		write_reg_le32(par->dc_regs, HRIR, 0x0100);
		write_reg_le32(par->dc_regs, CMR, 0x00ff);
		write_reg_le32(par->dc_regs, SRGCTL, 0x0073);
	} else {
		write_reg_le32(par->dc_regs, HRIR, 0x0200);
		write_reg_le32(par->dc_regs, CMR, 0x01ff);
		write_reg_le32(par->dc_regs, SRGCTL, 0x0003);
	}

	switch (info->fix.smem_len) {
		case 0x200000:
			scr = 0x059d | byteswap;
			break;
		/* case 0x400000:
		   case 0x800000: */
		default:
			pitch >>= 1;
			scr = 0x150dd | byteswap;
			break;
	}

	write_reg_le32(par->dc_regs, SCR, scr);
	write_reg_le32(par->dc_regs, SPR, pitch);
	write_reg_le32(par->dc_regs, STGCTL, ctl);
}