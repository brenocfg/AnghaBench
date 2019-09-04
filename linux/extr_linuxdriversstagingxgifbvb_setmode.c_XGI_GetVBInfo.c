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
struct vb_device_info {unsigned short ModeType; int VBType; unsigned short VBInfo; int /*<<< orphan*/  SetFlag; int /*<<< orphan*/  P3d4; } ;
struct TYPE_2__ {unsigned short Ext_ModeFlag; } ;

/* Variables and functions */
 unsigned short CRT2Mode ; 
 unsigned short DisableCRT2Display ; 
 unsigned short DriverMode ; 
 unsigned short EnableDualEdge ; 
 unsigned short ModeTypeMask ; 
 int /*<<< orphan*/  ReserveTVOption ; 
 unsigned short SetCRT2ToDualEdge ; 
 unsigned short SetCRT2ToHiVision ; 
 unsigned short SetCRT2ToLCD ; 
 unsigned short SetCRT2ToRAMDAC ; 
 unsigned short SetCRT2ToSCART ; 
 unsigned short SetCRT2ToTV ; 
 unsigned short SetCRT2ToYPbPr525750 ; 
 unsigned short SetInSlaveMode ; 
 unsigned short SetSimuScanMode ; 
 unsigned short SetToLCDA ; 
 unsigned short SetYPbPr ; 
 unsigned short SwitchCRT2 ; 
 int VB_NoLCD ; 
 int VB_SIS301LV ; 
 int VB_SIS302B ; 
 int VB_SIS302LV ; 
 int VB_XGI301C ; 
 TYPE_1__* XGI330_EModeIDTable ; 
 unsigned short XGI_SetCRT2ToLCDA ; 
 unsigned short YPbPrMode ; 
 unsigned short YPbPrMode1080i ; 
 unsigned short xgifb_reg_get (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void XGI_GetVBInfo(unsigned short ModeIdIndex,
			  struct vb_device_info *pVBInfo)
{
	unsigned short tempax, push, tempbx, temp, modeflag;

	modeflag = XGI330_EModeIDTable[ModeIdIndex].Ext_ModeFlag;
	pVBInfo->SetFlag = 0;
	pVBInfo->ModeType = modeflag & ModeTypeMask;
	tempbx = 0;

	if (!(pVBInfo->VBType & 0xFFFF))
		return;

	/* Check Display Device */
	temp = xgifb_reg_get(pVBInfo->P3d4, 0x30);
	tempbx = tempbx | temp;
	temp = xgifb_reg_get(pVBInfo->P3d4, 0x31);
	push = temp;
	push <<= 8;
	tempax = temp << 8;
	tempbx = tempbx | tempax;
	temp = SetCRT2ToDualEdge | SetCRT2ToYPbPr525750 | XGI_SetCRT2ToLCDA
		| SetInSlaveMode | DisableCRT2Display;
	temp = 0xFFFF ^ temp;
	tempbx &= temp;

	temp = xgifb_reg_get(pVBInfo->P3d4, 0x38);

	if (pVBInfo->VBType & (VB_SIS302B | VB_SIS301LV | VB_SIS302LV |
			       VB_XGI301C)) {
		if (temp & EnableDualEdge) {
			tempbx |= SetCRT2ToDualEdge;
			if (temp & SetToLCDA)
				tempbx |= XGI_SetCRT2ToLCDA;
		}
	}

	if (pVBInfo->VBType & (VB_SIS301LV | VB_SIS302LV | VB_XGI301C)) {
		if (temp & SetYPbPr) {
			/* shampoo add for new scratch */
			temp = xgifb_reg_get(pVBInfo->P3d4, 0x35);
			temp &= YPbPrMode;
			tempbx |= SetCRT2ToHiVision;

			if (temp != YPbPrMode1080i) {
				tempbx &= ~SetCRT2ToHiVision;
				tempbx |= SetCRT2ToYPbPr525750;
			}
		}
	}

	tempax = push; /* restore CR31 */

	temp = 0x09FC;

	if (!(tempbx & temp)) {
		tempax |= DisableCRT2Display;
		tempbx = 0;
	}

	if (!(pVBInfo->VBType & VB_NoLCD)) {
		if (tempbx & XGI_SetCRT2ToLCDA) {
			if (tempbx & SetSimuScanMode)
				tempbx &= (~(SetCRT2ToLCD | SetCRT2ToRAMDAC |
					     SwitchCRT2));
			else
				tempbx &= (~(SetCRT2ToLCD | SetCRT2ToRAMDAC |
					     SetCRT2ToTV | SwitchCRT2));
		}
	}

	/* shampoo add */
	/* for driver abnormal */
	if (!(tempbx & (SwitchCRT2 | SetSimuScanMode))) {
		if (tempbx & SetCRT2ToRAMDAC) {
			tempbx &= (0xFF00 | SetCRT2ToRAMDAC |
				   SwitchCRT2 | SetSimuScanMode);
			tempbx &= (0x00FF | (~SetCRT2ToYPbPr525750));
		}
	}

	if (!(pVBInfo->VBType & VB_NoLCD)) {
		if (tempbx & SetCRT2ToLCD) {
			tempbx &= (0xFF00 | SetCRT2ToLCD | SwitchCRT2 |
				   SetSimuScanMode);
			tempbx &= (0x00FF | (~SetCRT2ToYPbPr525750));
		}
	}

	if (tempbx & SetCRT2ToSCART) {
		tempbx &= (0xFF00 | SetCRT2ToSCART | SwitchCRT2 |
			   SetSimuScanMode);
		tempbx &= (0x00FF | (~SetCRT2ToYPbPr525750));
	}

	if (tempbx & SetCRT2ToYPbPr525750)
		tempbx &= (0xFF00 | SwitchCRT2 | SetSimuScanMode);

	if (tempbx & SetCRT2ToHiVision)
		tempbx &= (0xFF00 | SetCRT2ToHiVision | SwitchCRT2 |
			   SetSimuScanMode);

	if (tempax & DisableCRT2Display) { /* Set Display Device Info */
		if (!(tempbx & (SwitchCRT2 | SetSimuScanMode)))
			tempbx = DisableCRT2Display;
	}

	if (!(tempbx & DisableCRT2Display)) {
		if (!(tempbx & DriverMode) || !(modeflag & CRT2Mode)) {
			if (!(tempbx & XGI_SetCRT2ToLCDA))
				tempbx |= (SetInSlaveMode | SetSimuScanMode);
		}

		/* LCD+TV can't support in slave mode
		 * (Force LCDA+TV->LCDB)
		 */
		if ((tempbx & SetInSlaveMode) && (tempbx & XGI_SetCRT2ToLCDA)) {
			tempbx ^= (SetCRT2ToLCD | XGI_SetCRT2ToLCDA |
				   SetCRT2ToDualEdge);
			pVBInfo->SetFlag |= ReserveTVOption;
		}
	}

	pVBInfo->VBInfo = tempbx;
}