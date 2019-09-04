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
struct vb_device_info {int VBInfo; int VBType; unsigned short VGAHDE; unsigned short VGAHT; int TVInfo; scalar_t__ LCDResInfo; int LCDInfo; unsigned short VGAVT; unsigned short VGAVDE; int /*<<< orphan*/  Part1Port; } ;
struct TYPE_2__ {unsigned short Ext_ModeFlag; unsigned short Ext_RESINFO; } ;

/* Variables and functions */
 unsigned short Charx8Dot ; 
 int DisableCRT2Display ; 
 unsigned short DoubleScanMode ; 
 unsigned short HalfDCLK ; 
 int LCDNonExpanding ; 
 int LCDRGB18Bit ; 
 scalar_t__ Panel_1024x768 ; 
 scalar_t__ Panel_1280x960 ; 
 int SetCRT2ToHiVision ; 
 int SetCRT2ToLCD ; 
 int SetCRT2ToTV ; 
 int SetInSlaveMode ; 
 int SetNTSCTV ; 
 int TVSetHiVision ; 
 int TVSetPAL ; 
 int TVSetYPbPr525p ; 
 int TVSetYPbPr750p ; 
 int TVSimuMode ; 
 int VB_SIS301B ; 
 int VB_SIS301LV ; 
 int VB_SIS302B ; 
 int VB_SIS302LV ; 
 int VB_XGI301C ; 
 TYPE_1__* XGI330_EModeIDTable ; 
 unsigned short XGI_GetVGAHT2 (struct vb_device_info*) ; 
 int XGI_LCDVESATiming ; 
 int /*<<< orphan*/  xgifb_reg_and_or (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,int,unsigned short) ; 

__attribute__((used)) static void XGI_SetLockRegs(unsigned short ModeNo, unsigned short ModeIdIndex,
			    struct vb_device_info *pVBInfo)
{
	unsigned short push1, push2, tempax, tempbx = 0, tempcx, temp, resinfo,
			modeflag;

	/* si+Ext_ResInfo */
	modeflag = XGI330_EModeIDTable[ModeIdIndex].Ext_ModeFlag;
	resinfo = XGI330_EModeIDTable[ModeIdIndex].Ext_RESINFO;

	if (!(pVBInfo->VBInfo & SetInSlaveMode))
		return;

	temp = 0xFF; /* set MAX HT */
	xgifb_reg_set(pVBInfo->Part1Port, 0x03, temp);
	tempcx = 0x08;

	if (pVBInfo->VBType & (VB_SIS301LV | VB_SIS302LV | VB_XGI301C))
		modeflag |= Charx8Dot;

	tempax = pVBInfo->VGAHDE; /* 0x04 Horizontal Display End */

	if (modeflag & HalfDCLK)
		tempax >>= 1;

	tempax = (tempax / tempcx) - 1;
	tempbx |= ((tempax & 0x00FF) << 8);
	temp = tempax & 0x00FF;
	xgifb_reg_set(pVBInfo->Part1Port, 0x04, temp);

	temp = (tempbx & 0xFF00) >> 8;

	if (pVBInfo->VBInfo & SetCRT2ToTV) {
		if (!(pVBInfo->VBType & (VB_SIS301B | VB_SIS302B | VB_SIS301LV
				| VB_SIS302LV | VB_XGI301C)))
			temp += 2;

		if ((pVBInfo->VBInfo & SetCRT2ToHiVision) &&
		    !(pVBInfo->VBType & VB_SIS301LV) && (resinfo == 7))
			temp -= 2;
	}

	/* 0x05 Horizontal Display Start */
	xgifb_reg_set(pVBInfo->Part1Port, 0x05, temp);
	/* 0x06 Horizontal Blank end */
	xgifb_reg_set(pVBInfo->Part1Port, 0x06, 0x03);

	if (!(pVBInfo->VBInfo & DisableCRT2Display)) { /* 030226 bainy */
		if (pVBInfo->VBInfo & SetCRT2ToTV)
			tempax = pVBInfo->VGAHT;
		else
			tempax = XGI_GetVGAHT2(pVBInfo);
	}

	if (tempax >= pVBInfo->VGAHT)
		tempax = pVBInfo->VGAHT;

	if (modeflag & HalfDCLK)
		tempax >>= 1;

	tempax = (tempax / tempcx) - 5;
	tempcx = tempax; /* 20030401 0x07 horizontal Retrace Start */
	if (pVBInfo->VBInfo & SetCRT2ToHiVision) {
		temp = (tempbx & 0x00FF) - 1;
		if (!(modeflag & HalfDCLK)) {
			temp -= 6;
			if (pVBInfo->TVInfo & TVSimuMode) {
				temp -= 4;
				temp -= 10;
			}
		}
	} else {
		tempbx = (tempbx & 0xFF00) >> 8;
		tempcx = (tempcx + tempbx) >> 1;
		temp = (tempcx & 0x00FF) + 2;

		if (pVBInfo->VBInfo & SetCRT2ToTV) {
			temp -= 1;
			if (!(modeflag & HalfDCLK)) {
				if ((modeflag & Charx8Dot)) {
					temp += 4;
					if (pVBInfo->VGAHDE >= 800)
						temp -= 6;
				}
			}
		} else if (!(modeflag & HalfDCLK)) {
			temp -= 4;
			if (pVBInfo->LCDResInfo != Panel_1280x960 &&
			    pVBInfo->VGAHDE >= 800) {
				temp -= 7;
				if (pVBInfo->VGAHDE >= 1280 &&
				    pVBInfo->LCDResInfo != Panel_1280x960 &&
				    (pVBInfo->LCDInfo & LCDNonExpanding))
					temp += 28;
			}
		}
	}

	/* 0x07 Horizontal Retrace Start */
	xgifb_reg_set(pVBInfo->Part1Port, 0x07, temp);
	/* 0x08 Horizontal Retrace End */
	xgifb_reg_set(pVBInfo->Part1Port, 0x08, 0);

	if (pVBInfo->VBInfo & SetCRT2ToTV) {
		if (pVBInfo->TVInfo & TVSimuMode) {
			if (ModeNo == 0x50) {
				if (pVBInfo->TVInfo == SetNTSCTV) {
					xgifb_reg_set(pVBInfo->Part1Port,
						      0x07, 0x30);
					xgifb_reg_set(pVBInfo->Part1Port,
						      0x08, 0x03);
				} else {
					xgifb_reg_set(pVBInfo->Part1Port,
						      0x07, 0x2f);
					xgifb_reg_set(pVBInfo->Part1Port,
						      0x08, 0x02);
				}
			}
		}
	}

	xgifb_reg_set(pVBInfo->Part1Port, 0x18, 0x03); /* 0x18 SR0B */
	xgifb_reg_and_or(pVBInfo->Part1Port, 0x19, 0xF0, 0x00);
	xgifb_reg_set(pVBInfo->Part1Port, 0x09, 0xFF); /* 0x09 Set Max VT */

	tempbx = pVBInfo->VGAVT;
	push1 = tempbx;
	tempcx = 0x121;
	tempbx = pVBInfo->VGAVDE; /* 0x0E Vertical Display End */

	if (tempbx == 357)
		tempbx = 350;
	if (tempbx == 360)
		tempbx = 350;
	if (tempbx == 375)
		tempbx = 350;
	if (tempbx == 405)
		tempbx = 400;
	if (tempbx == 525)
		tempbx = 480;

	push2 = tempbx;

	if (pVBInfo->VBInfo & SetCRT2ToLCD) {
		if (pVBInfo->LCDResInfo == Panel_1024x768) {
			if (!(pVBInfo->LCDInfo & XGI_LCDVESATiming)) {
				if (tempbx == 350)
					tempbx += 5;
				if (tempbx == 480)
					tempbx += 5;
			}
		}
	}
	tempbx--;
	tempbx--;
	temp = tempbx & 0x00FF;
	/* 0x10 vertical Blank Start */
	xgifb_reg_set(pVBInfo->Part1Port, 0x10, temp);
	tempbx = push2;
	tempbx--;
	temp = tempbx & 0x00FF;
	xgifb_reg_set(pVBInfo->Part1Port, 0x0E, temp);

	if (tempbx & 0x0100)
		tempcx |= 0x0002;

	tempax = 0x000B;

	if (modeflag & DoubleScanMode)
		tempax |= 0x08000;

	if (tempbx & 0x0200)
		tempcx |= 0x0040;

	temp = (tempax & 0xFF00) >> 8;
	xgifb_reg_set(pVBInfo->Part1Port, 0x0B, temp);

	if (tempbx & 0x0400)
		tempcx |= 0x0600;

	/* 0x11 Vertical Blank End */
	xgifb_reg_set(pVBInfo->Part1Port, 0x11, 0x00);

	tempax = push1;
	tempax -= tempbx; /* 0x0C Vertical Retrace Start */
	tempax >>= 2;
	push1 = tempax; /* push ax */

	if (resinfo != 0x09) {
		tempax <<= 1;
		tempbx += tempax;
	}

	if (pVBInfo->VBInfo & SetCRT2ToHiVision) {
		if ((pVBInfo->VBType & VB_SIS301LV) &&
		    !(pVBInfo->TVInfo & TVSetHiVision)) {
			if ((pVBInfo->TVInfo & TVSimuMode) &&
			    (pVBInfo->TVInfo & TVSetPAL)) {
				if (!(pVBInfo->VBType & VB_SIS301LV) ||
				    !(pVBInfo->TVInfo &
				      (TVSetYPbPr525p |
				       TVSetYPbPr750p |
				       TVSetHiVision)))
					tempbx += 40;
			}
		} else {
			tempbx -= 10;
		}
	} else if (pVBInfo->TVInfo & TVSimuMode) {
		if (pVBInfo->TVInfo & TVSetPAL) {
			if (pVBInfo->VBType & VB_SIS301LV) {
				if (!(pVBInfo->TVInfo &
				    (TVSetYPbPr525p |
				     TVSetYPbPr750p |
				     TVSetHiVision)))
					tempbx += 40;
			} else {
				tempbx += 40;
			}
		}
	}
	tempax = push1;
	tempax >>= 2;
	tempax++;
	tempax += tempbx;
	push1 = tempax; /* push ax */

	if ((pVBInfo->TVInfo & TVSetPAL)) {
		if (tempbx <= 513) {
			if (tempax >= 513)
				tempbx = 513;
		}
	}

	temp = tempbx & 0x00FF;
	xgifb_reg_set(pVBInfo->Part1Port, 0x0C, temp);
	tempbx--;
	temp = tempbx & 0x00FF;
	xgifb_reg_set(pVBInfo->Part1Port, 0x10, temp);

	if (tempbx & 0x0100)
		tempcx |= 0x0008;

	if (tempbx & 0x0200)
		xgifb_reg_and_or(pVBInfo->Part1Port, 0x0B, 0x0FF, 0x20);

	tempbx++;

	if (tempbx & 0x0100)
		tempcx |= 0x0004;

	if (tempbx & 0x0200)
		tempcx |= 0x0080;

	if (tempbx & 0x0400)
		tempcx |= 0x0C00;

	tempbx = push1; /* pop ax */
	temp = tempbx & 0x00FF;
	temp &= 0x0F;
	/* 0x0D vertical Retrace End */
	xgifb_reg_set(pVBInfo->Part1Port, 0x0D, temp);

	if (tempbx & 0x0010)
		tempcx |= 0x2000;

	temp = tempcx & 0x00FF;
	xgifb_reg_set(pVBInfo->Part1Port, 0x0A, temp); /* 0x0A CR07 */
	temp = (tempcx & 0x0FF00) >> 8;
	xgifb_reg_set(pVBInfo->Part1Port, 0x17, temp); /* 0x17 SR0A */
	tempax = modeflag;
	temp = (tempax & 0xFF00) >> 8;

	temp = (temp >> 1) & 0x09;

	if (pVBInfo->VBType & (VB_SIS301LV | VB_SIS302LV | VB_XGI301C))
		temp |= 0x01;

	xgifb_reg_set(pVBInfo->Part1Port, 0x16, temp); /* 0x16 SR01 */
	xgifb_reg_set(pVBInfo->Part1Port, 0x0F, 0); /* 0x0F CR14 */
	xgifb_reg_set(pVBInfo->Part1Port, 0x12, 0); /* 0x12 CR17 */

	if (pVBInfo->LCDInfo & LCDRGB18Bit)
		temp = 0x80;
	else
		temp = 0x00;

	xgifb_reg_set(pVBInfo->Part1Port, 0x1A, temp); /* 0x1A SR0E */
}