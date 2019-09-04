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
struct vb_device_info {unsigned short RVBHCFACT; unsigned short RVBHCMAX; int VGAHT; int VGAVT; unsigned short VBInfo; unsigned short VGAHDE; int TVInfo; unsigned long VDE; unsigned short RVBHRS; unsigned long VGAVDE; int VBType; unsigned short HT; int /*<<< orphan*/  Part4Port; } ;
struct TYPE_2__ {unsigned short Ext_ModeFlag; } ;

/* Variables and functions */
 unsigned short HalfDCLK ; 
 int NTSC1024x768 ; 
 unsigned short SetCRT2ToHiVision ; 
 int SetCRT2ToLCD ; 
 unsigned short SetCRT2ToTV ; 
 int SetInSlaveMode ; 
 int TVSetHiVision ; 
 int TVSetYPbPr525p ; 
 int TVSetYPbPr750p ; 
 int TVSimuMode ; 
 int VB_SIS301B ; 
 int VB_SIS301LV ; 
 int VB_SIS302B ; 
 int VB_SIS302LV ; 
 int VB_XGI301C ; 
 TYPE_1__* XGI330_EModeIDTable ; 
 scalar_t__ XGI_IsLCDDualLink (struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_SetCRT2VCLK (unsigned short,unsigned short,struct vb_device_info*) ; 
 int /*<<< orphan*/  xgifb_reg_and_or (int /*<<< orphan*/ ,int,int,unsigned short) ; 
 int /*<<< orphan*/  xgifb_reg_or (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,int,unsigned short) ; 

__attribute__((used)) static void XGI_SetGroup4(unsigned short ModeIdIndex,
			  unsigned short RefreshRateTableIndex,
			  struct vb_device_info *pVBInfo)
{
	unsigned short tempax, tempcx, tempbx, modeflag, temp, temp2;

	unsigned long tempebx, tempeax, templong;

	/* si+Ext_ResInfo */
	modeflag = XGI330_EModeIDTable[ModeIdIndex].Ext_ModeFlag;
	temp = pVBInfo->RVBHCFACT;
	xgifb_reg_set(pVBInfo->Part4Port, 0x13, temp);

	tempbx = pVBInfo->RVBHCMAX;
	temp = tempbx & 0x00FF;
	xgifb_reg_set(pVBInfo->Part4Port, 0x14, temp);
	temp2 = ((tempbx & 0xFF00) >> 8) << 7;
	tempcx = pVBInfo->VGAHT - 1;
	temp = tempcx & 0x00FF;
	xgifb_reg_set(pVBInfo->Part4Port, 0x16, temp);

	temp = ((tempcx & 0xFF00) >> 8) << 3;
	temp2 |= temp;

	tempcx = pVBInfo->VGAVT - 1;
	if (!(pVBInfo->VBInfo & SetCRT2ToTV))
		tempcx -= 5;

	temp = tempcx & 0x00FF;
	xgifb_reg_set(pVBInfo->Part4Port, 0x17, temp);
	temp = temp2 | ((tempcx & 0xFF00) >> 8);
	xgifb_reg_set(pVBInfo->Part4Port, 0x15, temp);
	xgifb_reg_or(pVBInfo->Part4Port, 0x0D, 0x08);
	tempcx = pVBInfo->VBInfo;
	tempbx = pVBInfo->VGAHDE;

	if (modeflag & HalfDCLK)
		tempbx >>= 1;

	if (XGI_IsLCDDualLink(pVBInfo))
		tempbx >>= 1;

	if (tempcx & SetCRT2ToHiVision) {
		temp = 0;
		if (tempbx <= 1024)
			temp = 0xA0;
		if (tempbx == 1280)
			temp = 0xC0;
	} else if (tempcx & SetCRT2ToTV) {
		temp = 0xA0;
		if (tempbx <= 800)
			temp = 0x80;
	} else {
		temp = 0x80;
		if (pVBInfo->VBInfo & SetCRT2ToLCD) {
			temp = 0;
			if (tempbx > 800)
				temp = 0x60;
		}
	}

	if (pVBInfo->TVInfo & (TVSetYPbPr525p | TVSetYPbPr750p)) {
		temp = 0x00;
		if (pVBInfo->VGAHDE == 1280)
			temp = 0x40;
		if (pVBInfo->VGAHDE == 1024)
			temp = 0x20;
	}
	xgifb_reg_and_or(pVBInfo->Part4Port, 0x0E, ~0xEF, temp);

	tempebx = pVBInfo->VDE;

	tempcx = pVBInfo->RVBHRS;
	temp = tempcx & 0x00FF;
	xgifb_reg_set(pVBInfo->Part4Port, 0x18, temp);

	tempeax = pVBInfo->VGAVDE;
	tempcx |= 0x04000;

	if (tempeax <= tempebx) {
		tempcx = tempcx & (~0x4000);
		tempeax = pVBInfo->VGAVDE;
	} else {
		tempeax -= tempebx;
	}

	templong = (tempeax * 256 * 1024) % tempebx;
	tempeax = (tempeax * 256 * 1024) / tempebx;
	tempebx = tempeax;

	if (templong != 0)
		tempebx++;

	temp = (unsigned short)(tempebx & 0x000000FF);
	xgifb_reg_set(pVBInfo->Part4Port, 0x1B, temp);

	temp = (unsigned short)((tempebx & 0x0000FF00) >> 8);
	xgifb_reg_set(pVBInfo->Part4Port, 0x1A, temp);
	tempbx = (unsigned short)(tempebx >> 16);
	temp = tempbx & 0x00FF;
	temp <<= 4;
	temp |= ((tempcx & 0xFF00) >> 8);
	xgifb_reg_set(pVBInfo->Part4Port, 0x19, temp);

	/* 301b */
	if (pVBInfo->VBType & (VB_SIS301B | VB_SIS302B | VB_SIS301LV
			| VB_SIS302LV | VB_XGI301C)) {
		temp = 0x0028;
		xgifb_reg_set(pVBInfo->Part4Port, 0x1C, temp);
		tempax = pVBInfo->VGAHDE;
		if (modeflag & HalfDCLK)
			tempax >>= 1;

		if (XGI_IsLCDDualLink(pVBInfo))
			tempax >>= 1;

		if (pVBInfo->VBInfo & SetCRT2ToLCD) {
			if (tempax > 800)
				tempax -= 800;
		} else if (pVBInfo->VGAHDE > 800) {
			if (pVBInfo->VGAHDE == 1024)
				tempax = (tempax * 25 / 32) - 1;
			else
				tempax = (tempax * 20 / 32) - 1;
		}
		tempax -= 1;

		temp = (tempax & 0xFF00) >> 8;
		temp = (temp & 0x0003) << 4;
		xgifb_reg_set(pVBInfo->Part4Port, 0x1E, temp);
		temp = tempax & 0x00FF;
		xgifb_reg_set(pVBInfo->Part4Port, 0x1D, temp);

		if (pVBInfo->VBInfo & (SetCRT2ToTV | SetCRT2ToHiVision)) {
			if (pVBInfo->VGAHDE > 800)
				xgifb_reg_or(pVBInfo->Part4Port, 0x1E, 0x08);
		}
		temp = 0x0036;

		if (pVBInfo->VBInfo & SetCRT2ToTV) {
			if (!(pVBInfo->TVInfo & (NTSC1024x768
					| TVSetYPbPr525p | TVSetYPbPr750p
					| TVSetHiVision))) {
				temp |= 0x0001;
				if ((pVBInfo->VBInfo & SetInSlaveMode) &&
				    !(pVBInfo->TVInfo & TVSimuMode))
					temp &= (~0x0001);
			}
		}

		xgifb_reg_and_or(pVBInfo->Part4Port, 0x1F, 0x00C0, temp);
		tempbx = pVBInfo->HT;
		if (XGI_IsLCDDualLink(pVBInfo))
			tempbx >>= 1;
		tempbx = (tempbx >> 1) - 2;
		temp = ((tempbx & 0x0700) >> 8) << 3;
		xgifb_reg_and_or(pVBInfo->Part4Port, 0x21, 0x00C0, temp);
		temp = tempbx & 0x00FF;
		xgifb_reg_set(pVBInfo->Part4Port, 0x22, temp);
	}
	/* end 301b */

	XGI_SetCRT2VCLK(ModeIdIndex, RefreshRateTableIndex, pVBInfo);
}