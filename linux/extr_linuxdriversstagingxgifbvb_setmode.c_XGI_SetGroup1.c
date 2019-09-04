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
struct vb_device_info {int VGAHT; int VGAHDE; int VBInfo; int VGAVT; int VGAVDE; int /*<<< orphan*/  Part1Port; } ;
struct TYPE_6__ {unsigned short Ext_ModeFlag; } ;
struct TYPE_5__ {unsigned short Ext_CRT1CRTC; } ;
struct TYPE_4__ {unsigned short* CR; } ;

/* Variables and functions */
 unsigned short DoubleScanMode ; 
 unsigned short HalfDCLK ; 
 unsigned short IndexMask ; 
 int SetCRT2ToRAMDAC ; 
 TYPE_3__* XGI330_EModeIDTable ; 
 TYPE_2__* XGI330_RefIndex ; 
 TYPE_1__* XGI_CRT1Table ; 
 int /*<<< orphan*/  xgifb_reg_and_or (int /*<<< orphan*/ ,int,int,unsigned short) ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,int,unsigned short) ; 

__attribute__((used)) static void XGI_SetGroup1(unsigned short ModeIdIndex,
			  unsigned short RefreshRateTableIndex,
			  struct vb_device_info *pVBInfo)
{
	unsigned short temp = 0, tempax = 0, tempbx = 0, tempcx = 0,
			pushbx = 0, CRT1Index, modeflag;

	CRT1Index = XGI330_RefIndex[RefreshRateTableIndex].Ext_CRT1CRTC;
	CRT1Index &= IndexMask;
	modeflag = XGI330_EModeIDTable[ModeIdIndex].Ext_ModeFlag;

	/* bainy change table name */
	if (modeflag & HalfDCLK) {
		/* BTVGA2HT 0x08,0x09 */
		temp = (pVBInfo->VGAHT / 2 - 1) & 0x0FF;
		xgifb_reg_set(pVBInfo->Part1Port, 0x08, temp);
		temp = (((pVBInfo->VGAHT / 2 - 1) & 0xFF00) >> 8) << 4;
		xgifb_reg_and_or(pVBInfo->Part1Port, 0x09, ~0x0F0, temp);
		/* BTVGA2HDEE 0x0A,0x0C */
		temp = (pVBInfo->VGAHDE / 2 + 16) & 0x0FF;
		xgifb_reg_set(pVBInfo->Part1Port, 0x0A, temp);
		tempcx = ((pVBInfo->VGAHT - pVBInfo->VGAHDE) / 2) >> 2;
		pushbx = pVBInfo->VGAHDE / 2 + 16;
		tempcx >>= 1;
		tempbx = pushbx + tempcx; /* bx BTVGA@HRS 0x0B,0x0C */
		tempcx += tempbx;

		if (pVBInfo->VBInfo & SetCRT2ToRAMDAC) {
			tempbx = XGI_CRT1Table[CRT1Index].CR[4];
			tempbx |= ((XGI_CRT1Table[CRT1Index].CR[14] &
						0xC0) << 2);
			tempbx = (tempbx - 3) << 3; /* (VGAHRS-3)*8 */
			tempcx = XGI_CRT1Table[CRT1Index].CR[5];
			tempcx &= 0x1F;
			temp = XGI_CRT1Table[CRT1Index].CR[15];
			temp = (temp & 0x04) << (5 - 2); /* VGAHRE D[5] */
			tempcx = ((tempcx | temp) - 3) << 3; /* (VGAHRE-3)*8 */
		}

		tempbx += 4;
		tempcx += 4;

		if (tempcx > (pVBInfo->VGAHT / 2))
			tempcx = pVBInfo->VGAHT / 2;

		temp = tempbx & 0x00FF;

		xgifb_reg_set(pVBInfo->Part1Port, 0x0B, temp);
	} else {
		temp = (pVBInfo->VGAHT - 1) & 0x0FF; /* BTVGA2HT 0x08,0x09 */
		xgifb_reg_set(pVBInfo->Part1Port, 0x08, temp);
		temp = (((pVBInfo->VGAHT - 1) & 0xFF00) >> 8) << 4;
		xgifb_reg_and_or(pVBInfo->Part1Port, 0x09, ~0x0F0, temp);
		/* BTVGA2HDEE 0x0A,0x0C */
		temp = (pVBInfo->VGAHDE + 16) & 0x0FF;
		xgifb_reg_set(pVBInfo->Part1Port, 0x0A, temp);
		tempcx = (pVBInfo->VGAHT - pVBInfo->VGAHDE) >> 2; /* cx */
		pushbx = pVBInfo->VGAHDE + 16;
		tempcx >>= 1;
		tempbx = pushbx + tempcx; /* bx BTVGA@HRS 0x0B,0x0C */
		tempcx += tempbx;

		if (pVBInfo->VBInfo & SetCRT2ToRAMDAC) {
			tempbx = XGI_CRT1Table[CRT1Index].CR[3];
			tempbx |= ((XGI_CRT1Table[CRT1Index].CR[5] &
						0xC0) << 2);
			tempbx = (tempbx - 3) << 3; /* (VGAHRS-3)*8 */
			tempcx = XGI_CRT1Table[CRT1Index].CR[4];
			tempcx &= 0x1F;
			temp = XGI_CRT1Table[CRT1Index].CR[6];
			temp = (temp & 0x04) << (5 - 2); /* VGAHRE D[5] */
			tempcx = ((tempcx | temp) - 3) << 3; /* (VGAHRE-3)*8 */
			tempbx += 16;
			tempcx += 16;
		}

		if (tempcx > pVBInfo->VGAHT)
			tempcx = pVBInfo->VGAHT;

		temp = tempbx & 0x00FF;
		xgifb_reg_set(pVBInfo->Part1Port, 0x0B, temp);
	}

	tempax = (tempax & 0x00FF) | (tempbx & 0xFF00);
	tempbx = pushbx;
	tempbx = (tempbx & 0x00FF) | ((tempbx & 0xFF00) << 4);
	tempax |= (tempbx & 0xFF00);
	temp = (tempax & 0xFF00) >> 8;
	xgifb_reg_set(pVBInfo->Part1Port, 0x0C, temp);
	temp = tempcx & 0x00FF;
	xgifb_reg_set(pVBInfo->Part1Port, 0x0D, temp);
	tempcx = pVBInfo->VGAVT - 1;
	temp = tempcx & 0x00FF;

	xgifb_reg_set(pVBInfo->Part1Port, 0x0E, temp);
	tempbx = pVBInfo->VGAVDE - 1;
	temp = tempbx & 0x00FF;
	xgifb_reg_set(pVBInfo->Part1Port, 0x0F, temp);
	temp = ((tempbx & 0xFF00) << 3) >> 8;
	temp |= ((tempcx & 0xFF00) >> 8);
	xgifb_reg_set(pVBInfo->Part1Port, 0x12, temp);

	/* BTVGA2VRS 0x10,0x11 */
	tempbx = (pVBInfo->VGAVT + pVBInfo->VGAVDE) >> 1;
	/* BTVGA2VRE 0x11 */
	tempcx = ((pVBInfo->VGAVT - pVBInfo->VGAVDE) >> 4) + tempbx + 1;

	if (pVBInfo->VBInfo & SetCRT2ToRAMDAC) {
		tempbx = XGI_CRT1Table[CRT1Index].CR[10];
		temp = XGI_CRT1Table[CRT1Index].CR[9];

		if (temp & 0x04)
			tempbx |= 0x0100;

		if (temp & 0x080)
			tempbx |= 0x0200;

		temp = XGI_CRT1Table[CRT1Index].CR[14];

		if (temp & 0x08)
			tempbx |= 0x0400;

		temp = XGI_CRT1Table[CRT1Index].CR[11];
		tempcx = (tempcx & 0xFF00) | (temp & 0x00FF);
	}

	temp = tempbx & 0x00FF;
	xgifb_reg_set(pVBInfo->Part1Port, 0x10, temp);
	temp = ((tempbx & 0xFF00) >> 8) << 4;
	temp = (tempcx & 0x000F) | (temp);
	xgifb_reg_set(pVBInfo->Part1Port, 0x11, temp);
	tempax = 0;

	if (modeflag & DoubleScanMode)
		tempax |= 0x80;

	if (modeflag & HalfDCLK)
		tempax |= 0x40;

	xgifb_reg_and_or(pVBInfo->Part1Port, 0x2C, ~0x0C0, tempax);
}