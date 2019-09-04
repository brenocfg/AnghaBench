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
struct vb_device_info {int VBInfo; unsigned short HDE; unsigned short VDE; int VT; int VBType; unsigned short LCDResInfo; int LCDInfo; unsigned short LCDHDES; unsigned short LCDHRS; unsigned short LCDVDES; unsigned short LCDVRS; unsigned short HT; int VGAVDE; int /*<<< orphan*/  Part2Port; } ;
struct XGI_LCDDesStruct {unsigned short LCDHDES; unsigned short LCDHRS; unsigned short LCDVDES; unsigned short LCDVRS; } ;

/* Variables and functions */
 int EnableScalingLCD ; 
 unsigned short PanelResInfo ; 
 unsigned short Panel_1024x768 ; 
 unsigned short Panel_1024x768x75 ; 
 unsigned short Panel_1280x1024 ; 
 unsigned short Panel_1280x1024x75 ; 
 unsigned short Panel_1400x1050 ; 
 int SetCRT2ToLCD ; 
 int VB_SIS301B ; 
 int VB_SIS301LV ; 
 int VB_SIS302B ; 
 int VB_SIS302LV ; 
 int VB_XGI301C ; 
 int /*<<< orphan*/  XGI_GetLCDSync (unsigned short*,unsigned short*,struct vb_device_info*) ; 
 struct XGI_LCDDesStruct* XGI_GetLcdPtr (int /*<<< orphan*/ ,unsigned short,struct vb_device_info*) ; 
 scalar_t__ XGI_IsLCDDualLink (struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_LCDDesDataTable ; 
 int XGI_LCDVESATiming ; 
 int /*<<< orphan*/  xgifb_lcddldes ; 
 int /*<<< orphan*/  xgifb_reg_and_or (int /*<<< orphan*/ ,int,int,unsigned short) ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,int,unsigned short) ; 

__attribute__((used)) static void XGI_SetLCDRegs(unsigned short ModeIdIndex,
			   struct vb_device_info *pVBInfo)
{
	unsigned short pushbx, tempax, tempbx, tempcx, temp, tempah,
			tempbh, tempch;

	struct XGI_LCDDesStruct const *LCDBDesPtr = NULL;

	/* si+Ext_ResInfo */
	if (!(pVBInfo->VBInfo & SetCRT2ToLCD))
		return;

	tempbx = pVBInfo->HDE; /* RHACTE=HDE-1 */

	if (XGI_IsLCDDualLink(pVBInfo))
		tempbx >>= 1;

	tempbx -= 1;
	temp = tempbx & 0x00FF;
	xgifb_reg_set(pVBInfo->Part2Port, 0x2C, temp);
	temp = (tempbx & 0xFF00) >> 8;
	temp <<= 4;
	xgifb_reg_and_or(pVBInfo->Part2Port, 0x2B, 0x0F, temp);
	temp = 0x01;

	xgifb_reg_set(pVBInfo->Part2Port, 0x0B, temp);
	tempbx = pVBInfo->VDE; /* RTVACTEO=(VDE-1)&0xFF */
	tempbx--;
	temp = tempbx & 0x00FF;
	xgifb_reg_set(pVBInfo->Part2Port, 0x03, temp);
	temp = ((tempbx & 0xFF00) >> 8) & 0x07;
	xgifb_reg_and_or(pVBInfo->Part2Port, 0x0C, ~0x07, temp);

	tempcx = pVBInfo->VT - 1;
	temp = tempcx & 0x00FF; /* RVTVT=VT-1 */
	xgifb_reg_set(pVBInfo->Part2Port, 0x19, temp);
	temp = (tempcx & 0xFF00) >> 8;
	temp <<= 5;
	xgifb_reg_set(pVBInfo->Part2Port, 0x1A, temp);
	xgifb_reg_and_or(pVBInfo->Part2Port, 0x09, 0xF0, 0x00);
	xgifb_reg_and_or(pVBInfo->Part2Port, 0x0A, 0xF0, 0x00);
	xgifb_reg_and_or(pVBInfo->Part2Port, 0x17, 0xFB, 0x00);
	xgifb_reg_and_or(pVBInfo->Part2Port, 0x18, 0xDF, 0x00);

	/* Customized LCDB Does not add */
	if ((pVBInfo->VBType & VB_SIS301LV) || (pVBInfo->VBType & VB_SIS302LV))
		LCDBDesPtr = XGI_GetLcdPtr(xgifb_lcddldes, ModeIdIndex,
					   pVBInfo);
	else
		LCDBDesPtr = XGI_GetLcdPtr(XGI_LCDDesDataTable, ModeIdIndex,
					   pVBInfo);

	tempah = pVBInfo->LCDResInfo;
	tempah &= PanelResInfo;

	if ((tempah == Panel_1024x768) || (tempah == Panel_1024x768x75)) {
		tempbx = 1024;
		tempcx = 768;
	} else if ((tempah == Panel_1280x1024) ||
		   (tempah == Panel_1280x1024x75)) {
		tempbx = 1280;
		tempcx = 1024;
	} else if (tempah == Panel_1400x1050) {
		tempbx = 1400;
		tempcx = 1050;
	} else {
		tempbx = 1600;
		tempcx = 1200;
	}

	if (pVBInfo->LCDInfo & EnableScalingLCD) {
		tempbx = pVBInfo->HDE;
		tempcx = pVBInfo->VDE;
	}

	pushbx = tempbx;
	tempax = pVBInfo->VT;
	pVBInfo->LCDHDES = LCDBDesPtr->LCDHDES;
	pVBInfo->LCDHRS = LCDBDesPtr->LCDHRS;
	pVBInfo->LCDVDES = LCDBDesPtr->LCDVDES;
	pVBInfo->LCDVRS = LCDBDesPtr->LCDVRS;
	tempbx = pVBInfo->LCDVDES;
	tempcx += tempbx;

	if (tempcx >= tempax)
		tempcx -= tempax; /* lcdvdes */

	temp = tempbx & 0x00FF; /* RVEQ1EQ=lcdvdes */
	xgifb_reg_set(pVBInfo->Part2Port, 0x05, temp);
	temp = tempcx & 0x00FF;
	xgifb_reg_set(pVBInfo->Part2Port, 0x06, temp);
	tempch = ((tempcx & 0xFF00) >> 8) & 0x07;
	tempbh = ((tempbx & 0xFF00) >> 8) & 0x07;
	tempah = tempch;
	tempah <<= 3;
	tempah |= tempbh;
	xgifb_reg_set(pVBInfo->Part2Port, 0x02, tempah);

	/* getlcdsync() */
	XGI_GetLCDSync(&tempax, &tempbx, pVBInfo);
	tempcx = tempbx;
	tempax = pVBInfo->VT;
	tempbx = pVBInfo->LCDVRS;

	tempcx += tempbx;
	if (tempcx >= tempax)
		tempcx -= tempax;

	temp = tempbx & 0x00FF; /* RTVACTEE=lcdvrs */
	xgifb_reg_set(pVBInfo->Part2Port, 0x04, temp);
	temp = (tempbx & 0xFF00) >> 8;
	temp <<= 4;
	temp |= (tempcx & 0x000F);
	xgifb_reg_set(pVBInfo->Part2Port, 0x01, temp);
	tempcx = pushbx;
	tempax = pVBInfo->HT;
	tempbx = pVBInfo->LCDHDES;
	tempbx &= 0x0FFF;

	if (XGI_IsLCDDualLink(pVBInfo)) {
		tempax >>= 1;
		tempbx >>= 1;
		tempcx >>= 1;
	}

	if (pVBInfo->VBType & VB_SIS302LV)
		tempbx += 1;

	if (pVBInfo->VBType & VB_XGI301C) /* tap4 */
		tempbx += 1;

	tempcx += tempbx;

	if (tempcx >= tempax)
		tempcx -= tempax;

	temp = tempbx & 0x00FF;
	xgifb_reg_set(pVBInfo->Part2Port, 0x1F, temp); /* RHBLKE=lcdhdes */
	temp = ((tempbx & 0xFF00) >> 8) << 4;
	xgifb_reg_set(pVBInfo->Part2Port, 0x20, temp);
	temp = tempcx & 0x00FF;
	xgifb_reg_set(pVBInfo->Part2Port, 0x23, temp); /* RHEQPLE=lcdhdee */
	temp = (tempcx & 0xFF00) >> 8;
	xgifb_reg_set(pVBInfo->Part2Port, 0x25, temp);

	XGI_GetLCDSync(&tempax, &tempbx, pVBInfo);
	tempcx = tempax;
	tempax = pVBInfo->HT;
	tempbx = pVBInfo->LCDHRS;
	if (XGI_IsLCDDualLink(pVBInfo)) {
		tempax >>= 1;
		tempbx >>= 1;
		tempcx >>= 1;
	}

	if (pVBInfo->VBType & VB_SIS302LV)
		tempbx += 1;

	tempcx += tempbx;

	if (tempcx >= tempax)
		tempcx -= tempax;

	temp = tempbx & 0x00FF; /* RHBURSTS=lcdhrs */
	xgifb_reg_set(pVBInfo->Part2Port, 0x1C, temp);

	temp = (tempbx & 0xFF00) >> 8;
	temp <<= 4;
	xgifb_reg_and_or(pVBInfo->Part2Port, 0x1D, ~0x0F0, temp);
	temp = tempcx & 0x00FF; /* RHSYEXP2S=lcdhre */
	xgifb_reg_set(pVBInfo->Part2Port, 0x21, temp);

	if (!(pVBInfo->LCDInfo & XGI_LCDVESATiming)) {
		if (pVBInfo->VGAVDE == 525) {
			if (pVBInfo->VBType & (VB_SIS301B | VB_SIS302B
					| VB_SIS301LV | VB_SIS302LV
					| VB_XGI301C))
				temp = 0xC6;
			else
				temp = 0xC4;

			xgifb_reg_set(pVBInfo->Part2Port, 0x2f, temp);
			xgifb_reg_set(pVBInfo->Part2Port, 0x30, 0xB3);
		}

		if (pVBInfo->VGAVDE == 420) {
			if (pVBInfo->VBType & (VB_SIS301B | VB_SIS302B
					| VB_SIS301LV | VB_SIS302LV
					| VB_XGI301C))
				temp = 0x4F;
			else
				temp = 0x4E;
			xgifb_reg_set(pVBInfo->Part2Port, 0x2f, temp);
		}
	}
}