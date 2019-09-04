#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int LVDS_Capability; unsigned short LVDSHT; unsigned short LVDSHDE; unsigned short LVDSHFP; unsigned short LVDSHSYNC; unsigned short LVDSVT; unsigned short LVDSVDE; unsigned short LVDSVFP; unsigned short LVDSVSYNC; unsigned short VCLKData1; unsigned short VCLKData2; } ;
struct xgifb_video_info {TYPE_1__ lvds_data; } ;
struct vb_device_info {int /*<<< orphan*/  P3da; int /*<<< orphan*/  P3c0; int /*<<< orphan*/  P3c4; int /*<<< orphan*/  P3d4; int /*<<< orphan*/  P3c2; int /*<<< orphan*/  P3cc; } ;
struct TYPE_6__ {unsigned short Ext_RESINFO; unsigned short Ext_ModeFlag; } ;
struct TYPE_5__ {unsigned short HTotal; unsigned short VTotal; } ;

/* Variables and functions */
 unsigned short Charx8Dot ; 
 unsigned short DoubleScanMode ; 
 int LCDPolarity ; 
 int XG27 ; 
 TYPE_3__* XGI330_EModeIDTable ; 
 TYPE_2__* XGI330_ModeResInfo ; 
 int /*<<< orphan*/  XGI_SetXG21FPBits (struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_SetXG27FPBits (struct vb_device_info*) ; 
 unsigned char inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgifb_reg_and_or (int /*<<< orphan*/ ,int,int,unsigned short) ; 
 unsigned char xgifb_reg_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xgifb_reg_or (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,int,unsigned short) ; 

__attribute__((used)) static void xgifb_set_lvds(struct xgifb_video_info *xgifb_info,
			   int chip_id,
			   unsigned short ModeIdIndex,
			   struct vb_device_info *pVBInfo)
{
	unsigned char temp, Miscdata;
	unsigned short xres, yres, modeflag, resindex;
	unsigned short LVDSHT, LVDSHBS, LVDSHRS, LVDSHRE, LVDSHBE;
	unsigned short LVDSVT, LVDSVBS, LVDSVRS, LVDSVRE, LVDSVBE;
	unsigned short value;

	temp = (unsigned char)((xgifb_info->lvds_data.LVDS_Capability &
				(LCDPolarity << 8)) >> 8);
	temp &= LCDPolarity;
	Miscdata = inb(pVBInfo->P3cc);

	outb((Miscdata & 0x3F) | temp, pVBInfo->P3c2);

	temp = xgifb_info->lvds_data.LVDS_Capability & LCDPolarity;
	/* SR35[7] FP VSync polarity */
	xgifb_reg_and_or(pVBInfo->P3c4, 0x35, ~0x80, temp & 0x80);
	/* SR30[5] FP HSync polarity */
	xgifb_reg_and_or(pVBInfo->P3c4, 0x30, ~0x20, (temp & 0x40) >> 1);

	if (chip_id == XG27)
		XGI_SetXG27FPBits(pVBInfo);
	else
		XGI_SetXG21FPBits(pVBInfo);

	resindex = XGI330_EModeIDTable[ModeIdIndex].Ext_RESINFO;
	xres = XGI330_ModeResInfo[resindex].HTotal; /* xres->ax */
	yres = XGI330_ModeResInfo[resindex].VTotal; /* yres->bx */
	/* si+St_ModeFlag */
	modeflag = XGI330_EModeIDTable[ModeIdIndex].Ext_ModeFlag;

	if (!(modeflag & Charx8Dot))
		xres = xres * 8 / 9;

	LVDSHT = xgifb_info->lvds_data.LVDSHT;

	LVDSHBS = xres + (xgifb_info->lvds_data.LVDSHDE - xres) / 2;

	if (LVDSHBS > LVDSHT)
		LVDSHBS -= LVDSHT;

	LVDSHRS = LVDSHBS + xgifb_info->lvds_data.LVDSHFP;
	if (LVDSHRS > LVDSHT)
		LVDSHRS -= LVDSHT;

	LVDSHRE = LVDSHRS + xgifb_info->lvds_data.LVDSHSYNC;
	if (LVDSHRE > LVDSHT)
		LVDSHRE -= LVDSHT;

	LVDSHBE = LVDSHBS + LVDSHT - xgifb_info->lvds_data.LVDSHDE;

	LVDSVT = xgifb_info->lvds_data.LVDSVT;

	LVDSVBS = yres + (xgifb_info->lvds_data.LVDSVDE - yres) / 2;
	if (modeflag & DoubleScanMode)
		LVDSVBS += yres / 2;

	if (LVDSVBS > LVDSVT)
		LVDSVBS -= LVDSVT;

	LVDSVRS = LVDSVBS + xgifb_info->lvds_data.LVDSVFP;
	if (LVDSVRS > LVDSVT)
		LVDSVRS -= LVDSVT;

	LVDSVRE = LVDSVRS + xgifb_info->lvds_data.LVDSVSYNC;
	if (LVDSVRE > LVDSVT)
		LVDSVRE -= LVDSVT;

	LVDSVBE = LVDSVBS + LVDSVT - xgifb_info->lvds_data.LVDSVDE;

	temp = xgifb_reg_get(pVBInfo->P3d4, 0x11);
	xgifb_reg_set(pVBInfo->P3d4, 0x11, temp & 0x7f); /* Unlock CRTC */

	if (!(modeflag & Charx8Dot))
		xgifb_reg_or(pVBInfo->P3c4, 0x1, 0x1);

	/* HT SR0B[1:0] CR00 */
	value = (LVDSHT >> 3) - 5;
	xgifb_reg_and_or(pVBInfo->P3c4, 0x0B, ~0x03, (value & 0x300) >> 8);
	xgifb_reg_set(pVBInfo->P3d4, 0x0, (value & 0xFF));

	/* HBS SR0B[5:4] CR02 */
	value = (LVDSHBS >> 3) - 1;
	xgifb_reg_and_or(pVBInfo->P3c4, 0x0B, ~0x30, (value & 0x300) >> 4);
	xgifb_reg_set(pVBInfo->P3d4, 0x2, (value & 0xFF));

	/* HBE SR0C[1:0] CR05[7] CR03[4:0] */
	value = (LVDSHBE >> 3) - 1;
	xgifb_reg_and_or(pVBInfo->P3c4, 0x0C, ~0x03, (value & 0xC0) >> 6);
	xgifb_reg_and_or(pVBInfo->P3d4, 0x05, ~0x80, (value & 0x20) << 2);
	xgifb_reg_and_or(pVBInfo->P3d4, 0x03, ~0x1F, value & 0x1F);

	/* HRS SR0B[7:6] CR04 */
	value = (LVDSHRS >> 3) + 2;
	xgifb_reg_and_or(pVBInfo->P3c4, 0x0B, ~0xC0, (value & 0x300) >> 2);
	xgifb_reg_set(pVBInfo->P3d4, 0x4, (value & 0xFF));

	/* Panel HRS SR2F[1:0] SR2E[7:0]  */
	value--;
	xgifb_reg_and_or(pVBInfo->P3c4, 0x2F, ~0x03, (value & 0x300) >> 8);
	xgifb_reg_set(pVBInfo->P3c4, 0x2E, (value & 0xFF));

	/* HRE SR0C[2] CR05[4:0] */
	value = (LVDSHRE >> 3) + 2;
	xgifb_reg_and_or(pVBInfo->P3c4, 0x0C, ~0x04, (value & 0x20) >> 3);
	xgifb_reg_and_or(pVBInfo->P3d4, 0x05, ~0x1F, value & 0x1F);

	/* Panel HRE SR2F[7:2]  */
	value--;
	xgifb_reg_and_or(pVBInfo->P3c4, 0x2F, ~0xFC, value << 2);

	/* VT SR0A[0] CR07[5][0] CR06 */
	value = LVDSVT - 2;
	xgifb_reg_and_or(pVBInfo->P3c4, 0x0A, ~0x01, (value & 0x400) >> 10);
	xgifb_reg_and_or(pVBInfo->P3d4, 0x07, ~0x20, (value & 0x200) >> 4);
	xgifb_reg_and_or(pVBInfo->P3d4, 0x07, ~0x01, (value & 0x100) >> 8);
	xgifb_reg_set(pVBInfo->P3d4, 0x06, (value & 0xFF));

	/* VBS SR0A[2] CR09[5] CR07[3] CR15 */
	value = LVDSVBS - 1;
	xgifb_reg_and_or(pVBInfo->P3c4, 0x0A, ~0x04, (value & 0x400) >> 8);
	xgifb_reg_and_or(pVBInfo->P3d4, 0x09, ~0x20, (value & 0x200) >> 4);
	xgifb_reg_and_or(pVBInfo->P3d4, 0x07, ~0x08, (value & 0x100) >> 5);
	xgifb_reg_set(pVBInfo->P3d4, 0x15, (value & 0xFF));

	/* VBE SR0A[4] CR16 */
	value = LVDSVBE - 1;
	xgifb_reg_and_or(pVBInfo->P3c4, 0x0A, ~0x10, (value & 0x100) >> 4);
	xgifb_reg_set(pVBInfo->P3d4, 0x16, (value & 0xFF));

	/* VRS SR0A[3] CR7[7][2] CR10 */
	value = LVDSVRS - 1;
	xgifb_reg_and_or(pVBInfo->P3c4, 0x0A, ~0x08, (value & 0x400) >> 7);
	xgifb_reg_and_or(pVBInfo->P3d4, 0x07, ~0x80, (value & 0x200) >> 2);
	xgifb_reg_and_or(pVBInfo->P3d4, 0x07, ~0x04, (value & 0x100) >> 6);
	xgifb_reg_set(pVBInfo->P3d4, 0x10, (value & 0xFF));

	if (chip_id == XG27) {
		/* Panel VRS SR35[2:0] SR34[7:0] */
		xgifb_reg_and_or(pVBInfo->P3c4, 0x35, ~0x07,
				 (value & 0x700) >> 8);
		xgifb_reg_set(pVBInfo->P3c4, 0x34, value & 0xFF);
	} else {
		/* Panel VRS SR3F[1:0] SR34[7:0] SR33[0] */
		xgifb_reg_and_or(pVBInfo->P3c4, 0x3F, ~0x03,
				 (value & 0x600) >> 9);
		xgifb_reg_set(pVBInfo->P3c4, 0x34, (value >> 1) & 0xFF);
		xgifb_reg_and_or(pVBInfo->P3d4, 0x33, ~0x01, value & 0x01);
	}

	/* VRE SR0A[5] CR11[3:0] */
	value = LVDSVRE - 1;
	xgifb_reg_and_or(pVBInfo->P3c4, 0x0A, ~0x20, (value & 0x10) << 1);
	xgifb_reg_and_or(pVBInfo->P3d4, 0x11, ~0x0F, value & 0x0F);

	/* Panel VRE SR3F[7:2] */
	if (chip_id == XG27)
		xgifb_reg_and_or(pVBInfo->P3c4, 0x3F, ~0xFC,
				 (value << 2) & 0xFC);
	else
		/* SR3F[7] has to be 0, h/w bug */
		xgifb_reg_and_or(pVBInfo->P3c4, 0x3F, ~0xFC,
				 (value << 2) & 0x7C);

	for (temp = 0, value = 0; temp < 3; temp++) {
		xgifb_reg_and_or(pVBInfo->P3c4, 0x31, ~0x30, value);
		xgifb_reg_set(pVBInfo->P3c4,
			      0x2B, xgifb_info->lvds_data.VCLKData1);
		xgifb_reg_set(pVBInfo->P3c4,
			      0x2C, xgifb_info->lvds_data.VCLKData2);
		value += 0x10;
	}

	if (!(modeflag & Charx8Dot)) {
		inb(pVBInfo->P3da); /* reset 3da */
		outb(0x13, pVBInfo->P3c0); /* set index */
		/* set data, panning = 0, shift left 1 dot*/
		outb(0x00, pVBInfo->P3c0);

		inb(pVBInfo->P3da); /* Enable Attribute */
		outb(0x20, pVBInfo->P3c0);

		inb(pVBInfo->P3da); /* reset 3da */
	}
}