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
struct vb_device_info {int VBInfo; int TVInfo; int SetFlag; unsigned short NewFlickerMode; unsigned short VDE; int VBType; unsigned short VGAHDE; unsigned short HT; int VGAVDE; unsigned short HDE; int /*<<< orphan*/  Part2Port; int /*<<< orphan*/  Part4Port; } ;
struct TYPE_2__ {unsigned short Ext_ModeFlag; } ;

/* Variables and functions */
 unsigned short Charx8Dot ; 
 unsigned short HalfDCLK ; 
 int NTSC1024x768 ; 
 int SetCRT2ToAVIDEO ; 
 int SetCRT2ToHiVision ; 
 int SetCRT2ToLCD ; 
 int SetCRT2ToSCART ; 
 int SetCRT2ToSVIDEO ; 
 int SetCRT2ToTV ; 
 int SetCRT2ToYPbPr525750 ; 
 int SetInSlaveMode ; 
 int TVSetHiVision ; 
 int TVSetPAL ; 
 int TVSetPALM ; 
 int TVSetYPbPr525i ; 
 int TVSetYPbPr525p ; 
 int TVSetYPbPr750p ; 
 int TVSimuMode ; 
 int VB_SIS301B ; 
 int VB_SIS301LV ; 
 int VB_SIS302B ; 
 int VB_SIS302LV ; 
 int VB_XGI301C ; 
 TYPE_1__* XGI330_EModeIDTable ; 
 unsigned char* XGI330_HiTVExtTiming ; 
 unsigned char* XGI330_HiTVSt1Timing ; 
 unsigned char* XGI330_HiTVSt2Timing ; 
 unsigned char* XGI330_HiTVTextTiming ; 
 unsigned char* XGI330_NTSCTiming ; 
 unsigned char* XGI330_PALTiming ; 
 unsigned char* XGI330_YPbPr525iTiming ; 
 unsigned char* XGI330_YPbPr525pTiming ; 
 unsigned char* XGI330_YPbPr750pTiming ; 
 unsigned short XGI_GetVGAHT2 (struct vb_device_info*) ; 
 scalar_t__ XGI_IsLCDDualLink (struct vb_device_info*) ; 
 unsigned char* XGI_NTSC1024AdjTime ; 
 int /*<<< orphan*/  xgifb_reg_and (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  xgifb_reg_and_or (int /*<<< orphan*/ ,int,int,int) ; 
 unsigned short xgifb_reg_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,int,unsigned char const) ; 

__attribute__((used)) static void XGI_SetGroup2(unsigned short ModeNo, unsigned short ModeIdIndex,
			  struct vb_device_info *pVBInfo)
{
	unsigned short i, j, tempax, tempbx, tempcx, temp, push1, push2,
			modeflag;
	unsigned char const *TimingPoint;

	unsigned long longtemp, tempeax, tempebx, temp2, tempecx;

	/* si+Ext_ResInfo */
	modeflag = XGI330_EModeIDTable[ModeIdIndex].Ext_ModeFlag;

	tempax = 0;

	if (!(pVBInfo->VBInfo & SetCRT2ToAVIDEO))
		tempax |= 0x0800;

	if (!(pVBInfo->VBInfo & SetCRT2ToSVIDEO))
		tempax |= 0x0400;

	if (pVBInfo->VBInfo & SetCRT2ToSCART)
		tempax |= 0x0200;

	if (!(pVBInfo->TVInfo & TVSetPAL))
		tempax |= 0x1000;

	if (pVBInfo->VBInfo & SetCRT2ToHiVision)
		tempax |= 0x0100;

	if (pVBInfo->TVInfo & (TVSetYPbPr525p | TVSetYPbPr750p))
		tempax &= 0xfe00;

	tempax = (tempax & 0xff00) >> 8;

	xgifb_reg_set(pVBInfo->Part2Port, 0x0, tempax);
	TimingPoint = XGI330_NTSCTiming;

	if (pVBInfo->TVInfo & TVSetPAL)
		TimingPoint = XGI330_PALTiming;

	if (pVBInfo->VBInfo & SetCRT2ToHiVision) {
		TimingPoint = XGI330_HiTVExtTiming;

		if (pVBInfo->VBInfo & SetInSlaveMode)
			TimingPoint = XGI330_HiTVSt2Timing;

		if (pVBInfo->SetFlag & TVSimuMode)
			TimingPoint = XGI330_HiTVSt1Timing;

		if (!(modeflag & Charx8Dot))
			TimingPoint = XGI330_HiTVTextTiming;
	}

	if (pVBInfo->VBInfo & SetCRT2ToYPbPr525750) {
		if (pVBInfo->TVInfo & TVSetYPbPr525i)
			TimingPoint = XGI330_YPbPr525iTiming;

		if (pVBInfo->TVInfo & TVSetYPbPr525p)
			TimingPoint = XGI330_YPbPr525pTiming;

		if (pVBInfo->TVInfo & TVSetYPbPr750p)
			TimingPoint = XGI330_YPbPr750pTiming;
	}

	for (i = 0x01, j = 0; i <= 0x2D; i++, j++)
		xgifb_reg_set(pVBInfo->Part2Port, i, TimingPoint[j]);

	for (i = 0x39; i <= 0x45; i++, j++)
		/* di->temp2[j] */
		xgifb_reg_set(pVBInfo->Part2Port, i, TimingPoint[j]);

	if (pVBInfo->VBInfo & SetCRT2ToTV)
		xgifb_reg_and_or(pVBInfo->Part2Port, 0x3A, 0x1F, 0x00);

	temp = pVBInfo->NewFlickerMode;
	temp &= 0x80;
	xgifb_reg_and_or(pVBInfo->Part2Port, 0x0A, 0xFF, temp);

	if (pVBInfo->TVInfo & TVSetPAL)
		tempax = 520;
	else
		tempax = 440;

	if (pVBInfo->VDE <= tempax) {
		tempax -= pVBInfo->VDE;
		tempax >>= 2;
		tempax = (tempax & 0x00FF) | ((tempax & 0x00FF) << 8);
		push1 = tempax;
		temp = (tempax & 0xFF00) >> 8;
		temp += (unsigned short)TimingPoint[0];

		if (pVBInfo->VBType & (VB_SIS301B | VB_SIS302B | VB_SIS301LV
				| VB_SIS302LV | VB_XGI301C)) {
			if (pVBInfo->VBInfo & (SetCRT2ToAVIDEO
					| SetCRT2ToSVIDEO | SetCRT2ToSCART
					| SetCRT2ToYPbPr525750)) {
				tempcx = pVBInfo->VGAHDE;
				if (tempcx >= 1024) {
					temp = 0x17; /* NTSC */
					if (pVBInfo->TVInfo & TVSetPAL)
						temp = 0x19; /* PAL */
				}
			}
		}

		xgifb_reg_set(pVBInfo->Part2Port, 0x01, temp);
		tempax = push1;
		temp = (tempax & 0xFF00) >> 8;
		temp += TimingPoint[1];

		if (pVBInfo->VBType & (VB_SIS301B | VB_SIS302B | VB_SIS301LV
				| VB_SIS302LV | VB_XGI301C)) {
			if ((pVBInfo->VBInfo & (SetCRT2ToAVIDEO
					| SetCRT2ToSVIDEO | SetCRT2ToSCART
					| SetCRT2ToYPbPr525750))) {
				tempcx = pVBInfo->VGAHDE;
				if (tempcx >= 1024) {
					temp = 0x1D; /* NTSC */
					if (pVBInfo->TVInfo & TVSetPAL)
						temp = 0x52; /* PAL */
				}
			}
		}
		xgifb_reg_set(pVBInfo->Part2Port, 0x02, temp);
	}

	/* 301b */
	tempcx = pVBInfo->HT;

	if (XGI_IsLCDDualLink(pVBInfo))
		tempcx >>= 1;

	tempcx -= 2;
	temp = tempcx & 0x00FF;
	xgifb_reg_set(pVBInfo->Part2Port, 0x1B, temp);

	temp = (tempcx & 0xFF00) >> 8;
	xgifb_reg_and_or(pVBInfo->Part2Port, 0x1D, ~0x0F, temp);

	tempcx = pVBInfo->HT >> 1;
	push1 = tempcx; /* push cx */
	tempcx += 7;

	if (pVBInfo->VBInfo & SetCRT2ToHiVision)
		tempcx -= 4;

	temp = tempcx & 0x00FF;
	temp <<= 4;
	xgifb_reg_and_or(pVBInfo->Part2Port, 0x22, 0x0F, temp);

	tempbx = TimingPoint[j] | ((TimingPoint[j + 1]) << 8);
	tempbx += tempcx;
	push2 = tempbx;
	temp = tempbx & 0x00FF;
	xgifb_reg_set(pVBInfo->Part2Port, 0x24, temp);
	temp = (tempbx & 0xFF00) >> 8;
	temp <<= 4;
	xgifb_reg_and_or(pVBInfo->Part2Port, 0x25, 0x0F, temp);

	tempbx = push2;
	tempbx = tempbx + 8;
	if (pVBInfo->VBInfo & SetCRT2ToHiVision) {
		tempbx = tempbx - 4;
		tempcx = tempbx;
	}

	temp = (tempbx & 0x00FF) << 4;
	xgifb_reg_and_or(pVBInfo->Part2Port, 0x29, 0x0F, temp);

	j += 2;
	tempcx += (TimingPoint[j] | ((TimingPoint[j + 1]) << 8));
	temp = tempcx & 0x00FF;
	xgifb_reg_set(pVBInfo->Part2Port, 0x27, temp);
	temp = ((tempcx & 0xFF00) >> 8) << 4;
	xgifb_reg_and_or(pVBInfo->Part2Port, 0x28, 0x0F, temp);

	tempcx += 8;
	if (pVBInfo->VBInfo & SetCRT2ToHiVision)
		tempcx -= 4;

	temp = tempcx & 0xFF;
	temp <<= 4;
	xgifb_reg_and_or(pVBInfo->Part2Port, 0x2A, 0x0F, temp);

	tempcx = push1; /* pop cx */
	j += 2;
	temp = TimingPoint[j] | ((TimingPoint[j + 1]) << 8);
	tempcx -= temp;
	temp = tempcx & 0x00FF;
	temp <<= 4;
	xgifb_reg_and_or(pVBInfo->Part2Port, 0x2D, 0x0F, temp);

	tempcx -= 11;

	if (!(pVBInfo->VBInfo & SetCRT2ToTV)) {
		tempax = XGI_GetVGAHT2(pVBInfo);
		tempcx = tempax - 1;
	}
	temp = tempcx & 0x00FF;
	xgifb_reg_set(pVBInfo->Part2Port, 0x2E, temp);

	tempbx = pVBInfo->VDE;

	if (pVBInfo->VGAVDE == 360)
		tempbx = 746;
	if (pVBInfo->VGAVDE == 375)
		tempbx = 746;
	if (pVBInfo->VGAVDE == 405)
		tempbx = 853;

	if (pVBInfo->VBInfo & SetCRT2ToTV) {
		if (pVBInfo->VBType &
		    (VB_SIS301LV | VB_SIS302LV | VB_XGI301C)) {
			if (!(pVBInfo->TVInfo &
			    (TVSetYPbPr525p | TVSetYPbPr750p)))
				tempbx >>= 1;
		} else {
			tempbx >>= 1;
		}
	}

	tempbx -= 2;
	temp = tempbx & 0x00FF;

	if (pVBInfo->VBInfo & SetCRT2ToHiVision) {
		if (pVBInfo->VBType & VB_SIS301LV) {
			if (pVBInfo->TVInfo & TVSetHiVision) {
				if (pVBInfo->VBInfo & SetInSlaveMode) {
					if (ModeNo == 0x2f)
						temp += 1;
				}
			}
		} else if (pVBInfo->VBInfo & SetInSlaveMode) {
			if (ModeNo == 0x2f)
				temp += 1;
		}
	}

	xgifb_reg_set(pVBInfo->Part2Port, 0x2F, temp);

	temp = (tempcx & 0xFF00) >> 8;
	temp |= ((tempbx & 0xFF00) >> 8) << 6;

	if (!(pVBInfo->VBInfo & SetCRT2ToHiVision)) {
		if (pVBInfo->VBType & VB_SIS301LV) {
			if (pVBInfo->TVInfo & TVSetHiVision) {
				temp |= 0x10;

				if (!(pVBInfo->VBInfo & SetCRT2ToSVIDEO))
					temp |= 0x20;
			}
		} else {
			temp |= 0x10;
			if (!(pVBInfo->VBInfo & SetCRT2ToSVIDEO))
				temp |= 0x20;
		}
	}

	xgifb_reg_set(pVBInfo->Part2Port, 0x30, temp);

	if (pVBInfo->VBType & (VB_SIS301B | VB_SIS302B | VB_SIS301LV
			| VB_SIS302LV | VB_XGI301C)) { /* TV gatingno */
		tempbx = pVBInfo->VDE;
		tempcx = tempbx - 2;

		if (pVBInfo->VBInfo & SetCRT2ToTV) {
			if (!(pVBInfo->TVInfo & (TVSetYPbPr525p
					| TVSetYPbPr750p)))
				tempbx >>= 1;
		}

		if (pVBInfo->VBType & (VB_SIS302LV | VB_XGI301C)) {
			temp = 0;
			if (tempcx & 0x0400)
				temp |= 0x20;

			if (tempbx & 0x0400)
				temp |= 0x40;

			xgifb_reg_set(pVBInfo->Part4Port, 0x10, temp);
		}

		temp = (((tempbx - 3) & 0x0300) >> 8) << 5;
		xgifb_reg_set(pVBInfo->Part2Port, 0x46, temp);
		temp = (tempbx - 3) & 0x00FF;
		xgifb_reg_set(pVBInfo->Part2Port, 0x47, temp);
	}

	tempbx = tempbx & 0x00FF;

	if (!(modeflag & HalfDCLK)) {
		tempcx = pVBInfo->VGAHDE;
		if (tempcx >= pVBInfo->HDE) {
			tempbx |= 0x2000;
			tempax &= 0x00FF;
		}
	}

	tempcx = 0x0101;

	if (pVBInfo->VBInfo & SetCRT2ToTV) { /* 301b */
		if (pVBInfo->VGAHDE >= 1024) {
			tempcx = 0x1920;
			if (pVBInfo->VGAHDE >= 1280) {
				tempcx = 0x1420;
				tempbx = tempbx & 0xDFFF;
			}
		}
	}

	if (!(tempbx & 0x2000)) {
		if (modeflag & HalfDCLK)
			tempcx = (tempcx & 0xFF00) | ((tempcx & 0x00FF) << 1);

		push1 = tempbx;
		tempeax = pVBInfo->VGAHDE;
		tempebx = (tempcx & 0xFF00) >> 8;
		longtemp = tempeax * tempebx;
		tempecx = tempcx & 0x00FF;
		longtemp = longtemp / tempecx;

		/* 301b */
		tempecx = 8 * 1024;

		if (pVBInfo->VBType & (VB_SIS301B | VB_SIS302B | VB_SIS301LV
				| VB_SIS302LV | VB_XGI301C)) {
			tempecx = tempecx * 8;
		}

		longtemp = longtemp * tempecx;
		tempecx = pVBInfo->HDE;
		temp2 = longtemp % tempecx;
		tempeax = longtemp / tempecx;
		if (temp2 != 0)
			tempeax += 1;

		tempax = (unsigned short)tempeax;

		/* 301b */
		if (pVBInfo->VBType & (VB_SIS301B | VB_SIS302B | VB_SIS301LV
				| VB_SIS302LV | VB_XGI301C)) {
			tempcx = ((tempax & 0xFF00) >> 5) >> 8;
		}
		/* end 301b */

		tempbx = push1;
		tempbx = (unsigned short)(((tempeax & 0x0000FF00) & 0x1F00)
				| (tempbx & 0x00FF));
		tempax = (unsigned short)(((tempeax & 0x000000FF) << 8)
				| (tempax & 0x00FF));
		temp = (tempax & 0xFF00) >> 8;
	} else {
		temp = (tempax & 0x00FF) >> 8;
	}

	xgifb_reg_set(pVBInfo->Part2Port, 0x44, temp);
	temp = (tempbx & 0xFF00) >> 8;
	xgifb_reg_and_or(pVBInfo->Part2Port, 0x45, ~0x03F, temp);
	temp = tempcx & 0x00FF;

	if (tempbx & 0x2000)
		temp = 0;

	if (!(pVBInfo->VBInfo & SetCRT2ToLCD))
		temp |= 0x18;

	xgifb_reg_and_or(pVBInfo->Part2Port, 0x46, ~0x1F, temp);
	if (pVBInfo->TVInfo & TVSetPAL) {
		tempbx = 0x0382;
		tempcx = 0x007e;
	} else {
		tempbx = 0x0369;
		tempcx = 0x0061;
	}

	temp = tempbx & 0x00FF;
	xgifb_reg_set(pVBInfo->Part2Port, 0x4b, temp);
	temp = tempcx & 0x00FF;
	xgifb_reg_set(pVBInfo->Part2Port, 0x4c, temp);

	temp = ((tempcx & 0xFF00) >> 8) & 0x03;
	temp <<= 2;
	temp |= ((tempbx & 0xFF00) >> 8) & 0x03;

	if (pVBInfo->VBInfo & SetCRT2ToYPbPr525750) {
		temp |= 0x10;

		if (pVBInfo->TVInfo & TVSetYPbPr525p)
			temp |= 0x20;

		if (pVBInfo->TVInfo & TVSetYPbPr750p)
			temp |= 0x60;
	}

	xgifb_reg_set(pVBInfo->Part2Port, 0x4d, temp);
	temp = xgifb_reg_get(pVBInfo->Part2Port, 0x43); /* 301b change */
	xgifb_reg_set(pVBInfo->Part2Port, 0x43, (unsigned short)(temp - 3));

	if (!(pVBInfo->TVInfo & (TVSetYPbPr525p | TVSetYPbPr750p))) {
		if (pVBInfo->TVInfo & NTSC1024x768) {
			TimingPoint = XGI_NTSC1024AdjTime;
			for (i = 0x1c, j = 0; i <= 0x30; i++, j++) {
				xgifb_reg_set(pVBInfo->Part2Port, i,
					      TimingPoint[j]);
			}
			xgifb_reg_set(pVBInfo->Part2Port, 0x43, 0x72);
		}
	}

	/* Modify for 301C PALM Support */
	if (pVBInfo->VBType & VB_XGI301C) {
		if (pVBInfo->TVInfo & TVSetPALM)
			xgifb_reg_and_or(pVBInfo->Part2Port, 0x4E, ~0x08,
					 0x08); /* PALM Mode */
	}

	if (pVBInfo->TVInfo & TVSetPALM) {
		tempax = xgifb_reg_get(pVBInfo->Part2Port, 0x01);
		tempax--;
		xgifb_reg_and(pVBInfo->Part2Port, 0x01, tempax);

		xgifb_reg_and(pVBInfo->Part2Port, 0x00, 0xEF);
	}

	if (pVBInfo->VBInfo & SetCRT2ToHiVision) {
		if (!(pVBInfo->VBInfo & SetInSlaveMode))
			xgifb_reg_set(pVBInfo->Part2Port, 0x0B, 0x00);
	}
}