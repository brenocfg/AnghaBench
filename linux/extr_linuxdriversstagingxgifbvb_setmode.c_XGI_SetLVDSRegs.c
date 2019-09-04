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
struct vb_device_info {scalar_t__ LCDResInfo; int LCDInfo; unsigned short HDE; unsigned short VDE; unsigned short VGAHDE; unsigned short VGAVDE; unsigned short HT; unsigned short VT; int VBType; int /*<<< orphan*/  Part1Port; int /*<<< orphan*/  Part4Port; } ;
struct XGI330_LCDDataDesStruct2 {unsigned short LCDHDES; unsigned short LCDHRS; unsigned short LCDHSync; unsigned short LCDVDES; unsigned short LCDVRS; unsigned short LCDVSync; } ;
struct TYPE_2__ {unsigned short Ext_ModeFlag; } ;

/* Variables and functions */
 int EnableScalingLCD ; 
 unsigned short HalfDCLK ; 
 scalar_t__ Panel_1024x768 ; 
 scalar_t__ Panel_1024x768x75 ; 
 scalar_t__ Panel_1280x1024 ; 
 scalar_t__ Panel_1280x1024x75 ; 
 scalar_t__ Panel_1400x1050 ; 
 int SetLCDtoNonExpanding ; 
 int VB_XGI301C ; 
 TYPE_1__* XGI330_EModeIDTable ; 
 int /*<<< orphan*/  XGI_EPLLCDDesDataPtr ; 
 int XGI_EnableLVDSDDA ; 
 int /*<<< orphan*/  XGI_GetLCDSync (unsigned short*,unsigned short*,struct vb_device_info*) ; 
 struct XGI330_LCDDataDesStruct2* XGI_GetLcdPtr (int /*<<< orphan*/ ,unsigned short,struct vb_device_info*) ; 
 int /*<<< orphan*/  xgifb_reg_and_or (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,int,unsigned short) ; 

__attribute__((used)) static void XGI_SetLVDSRegs(unsigned short ModeIdIndex,
			    struct vb_device_info *pVBInfo)
{
	unsigned short tempbx, tempax, tempcx, tempdx, push1, push2, modeflag;
	unsigned long temp, temp1, temp2, temp3, push3;
	struct XGI330_LCDDataDesStruct2 const *LCDPtr1 = NULL;

	modeflag = XGI330_EModeIDTable[ModeIdIndex].Ext_ModeFlag;
	LCDPtr1 = XGI_GetLcdPtr(XGI_EPLLCDDesDataPtr, ModeIdIndex, pVBInfo);

	XGI_GetLCDSync(&tempax, &tempbx, pVBInfo);
	push1 = tempbx;
	push2 = tempax;

	/* GetLCDResInfo */
	if ((pVBInfo->LCDResInfo == Panel_1024x768) ||
	    (pVBInfo->LCDResInfo == Panel_1024x768x75)) {
		tempax = 1024;
		tempbx = 768;
	} else if ((pVBInfo->LCDResInfo == Panel_1280x1024) ||
		   (pVBInfo->LCDResInfo == Panel_1280x1024x75)) {
		tempax = 1280;
		tempbx = 1024;
	} else if (pVBInfo->LCDResInfo == Panel_1400x1050) {
		tempax = 1400;
		tempbx = 1050;
	} else {
		tempax = 1600;
		tempbx = 1200;
	}

	if (pVBInfo->LCDInfo & SetLCDtoNonExpanding) {
		pVBInfo->HDE = tempax;
		pVBInfo->VDE = tempbx;
		pVBInfo->VGAHDE = tempax;
		pVBInfo->VGAVDE = tempbx;
	}

	tempax = pVBInfo->HT;

	tempbx = LCDPtr1->LCDHDES;

	tempcx = pVBInfo->HDE;
	tempbx = tempbx & 0x0fff;
	tempcx += tempbx;

	if (tempcx >= tempax)
		tempcx -= tempax;

	xgifb_reg_set(pVBInfo->Part1Port, 0x1A, tempbx & 0x07);

	tempcx >>= 3;
	tempbx >>= 3;

	xgifb_reg_set(pVBInfo->Part1Port, 0x16,
		      (unsigned short)(tempbx & 0xff));
	xgifb_reg_set(pVBInfo->Part1Port, 0x17,
		      (unsigned short)(tempcx & 0xff));

	tempax = pVBInfo->HT;

	tempbx = LCDPtr1->LCDHRS;

	tempcx = push2;

	if (pVBInfo->LCDInfo & EnableScalingLCD)
		tempcx = LCDPtr1->LCDHSync;

	tempcx += tempbx;

	if (tempcx >= tempax)
		tempcx -= tempax;

	tempax = tempbx & 0x07;
	tempax >>= 5;
	tempcx >>= 3;
	tempbx >>= 3;

	tempcx &= 0x1f;
	tempax |= tempcx;

	xgifb_reg_set(pVBInfo->Part1Port, 0x15, tempax);
	xgifb_reg_set(pVBInfo->Part1Port, 0x14,
		      (unsigned short)(tempbx & 0xff));

	tempax = pVBInfo->VT;
	tempbx = LCDPtr1->LCDVDES;
	tempcx = pVBInfo->VDE;

	tempbx = tempbx & 0x0fff;
	tempcx += tempbx;
	if (tempcx >= tempax)
		tempcx -= tempax;

	xgifb_reg_set(pVBInfo->Part1Port, 0x1b,
		      (unsigned short)(tempbx & 0xff));
	xgifb_reg_set(pVBInfo->Part1Port, 0x1c,
		      (unsigned short)(tempcx & 0xff));

	tempbx = (tempbx >> 8) & 0x07;
	tempcx = (tempcx >> 8) & 0x07;

	xgifb_reg_set(pVBInfo->Part1Port, 0x1d,
		      (unsigned short)((tempcx << 3) | tempbx));

	tempax = pVBInfo->VT;
	tempbx = LCDPtr1->LCDVRS;

	tempcx = push1;

	if (pVBInfo->LCDInfo & EnableScalingLCD)
		tempcx = LCDPtr1->LCDVSync;

	tempcx += tempbx;
	if (tempcx >= tempax)
		tempcx -= tempax;

	xgifb_reg_set(pVBInfo->Part1Port, 0x18,
		      (unsigned short)(tempbx & 0xff));
	xgifb_reg_and_or(pVBInfo->Part1Port, 0x19, ~0x0f,
			 (unsigned short)(tempcx & 0x0f));

	tempax = ((tempbx >> 8) & 0x07) << 3;

	tempbx = pVBInfo->VGAVDE;
	if (tempbx != pVBInfo->VDE)
		tempax |= 0x40;

	if (pVBInfo->LCDInfo & XGI_EnableLVDSDDA)
		tempax |= 0x40;

	xgifb_reg_and_or(pVBInfo->Part1Port, 0x1a, 0x07, tempax);

	tempbx = pVBInfo->VDE;
	tempax = pVBInfo->VGAVDE;

	temp = tempax; /* 0430 ylshieh */
	temp1 = (temp << 18) / tempbx;

	tempdx = (unsigned short)((temp << 18) % tempbx);

	if (tempdx != 0)
		temp1 += 1;

	temp2 = temp1;
	push3 = temp2;

	xgifb_reg_set(pVBInfo->Part1Port, 0x37,	(unsigned short)(temp2 & 0xff));
	xgifb_reg_set(pVBInfo->Part1Port, 0x36,	(unsigned short)((temp2 >> 8) & 0xff));

	tempbx = (unsigned short)(temp2 >> 16);
	tempax = tempbx & 0x03;

	tempbx = pVBInfo->VGAVDE;
	if (tempbx == pVBInfo->VDE)
		tempax |= 0x04;

	xgifb_reg_set(pVBInfo->Part1Port, 0x35, tempax);

	if (pVBInfo->VBType & VB_XGI301C) {
		temp2 = push3;
		xgifb_reg_set(pVBInfo->Part4Port,
			      0x3c,
			      (unsigned short)(temp2 & 0xff));
		xgifb_reg_set(pVBInfo->Part4Port,
			      0x3b,
			      (unsigned short)((temp2 >> 8) &
			      0xff));
		tempbx = (unsigned short)(temp2 >> 16);
		xgifb_reg_and_or(pVBInfo->Part4Port, 0x3a, ~0xc0,
				 (unsigned short)((tempbx & 0xff) << 6));

		tempcx = pVBInfo->VGAVDE;
		if (tempcx == pVBInfo->VDE)
			xgifb_reg_and_or(pVBInfo->Part4Port, 0x30, ~0x0c, 0x00);
		else
			xgifb_reg_and_or(pVBInfo->Part4Port, 0x30, ~0x0c, 0x08);
	}

	tempcx = pVBInfo->VGAHDE;
	tempbx = pVBInfo->HDE;

	temp1 = tempcx << 16;

	tempax = (unsigned short)(temp1 / tempbx);

	if ((tempbx & 0xffff) == (tempcx & 0xffff))
		tempax = 65535;

	temp3 = tempax;
	temp1 = pVBInfo->VGAHDE << 16;

	temp1 /= temp3;
	temp3 <<= 16;
	temp1 -= 1;

	temp3 = (temp3 & 0xffff0000) + (temp1 & 0xffff);

	tempax = (unsigned short)(temp3 & 0xff);
	xgifb_reg_set(pVBInfo->Part1Port, 0x1f, tempax);

	temp1 = pVBInfo->VGAVDE << 18;
	temp1 = temp1 / push3;
	tempbx = (unsigned short)(temp1 & 0xffff);

	if (pVBInfo->LCDResInfo == Panel_1024x768)
		tempbx -= 1;

	tempax = ((tempbx >> 8) & 0xff) << 3;
	tempax |= (unsigned short)((temp3 >> 8) & 0x07);
	xgifb_reg_set(pVBInfo->Part1Port, 0x20,
		      (unsigned short)(tempax & 0xff));
	xgifb_reg_set(pVBInfo->Part1Port, 0x21,
		      (unsigned short)(tempbx & 0xff));

	temp3 >>= 16;

	if (modeflag & HalfDCLK)
		temp3 >>= 1;

	xgifb_reg_set(pVBInfo->Part1Port, 0x22,
		      (unsigned short)((temp3 >> 8) & 0xff));
	xgifb_reg_set(pVBInfo->Part1Port, 0x23,
		      (unsigned short)(temp3 & 0xff));
}