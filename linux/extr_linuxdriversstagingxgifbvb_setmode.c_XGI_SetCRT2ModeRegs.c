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
struct vb_device_info {int VBInfo; short ModeType; int LCDInfo; int TVInfo; scalar_t__ LCDResInfo; int VBType; int /*<<< orphan*/  Part4Port; int /*<<< orphan*/  Part1Port; } ;

/* Variables and functions */
 int DisableCRT2Display ; 
 int DriverMode ; 
 short ModeVGA ; 
 scalar_t__ Panel_1280x1024 ; 
 scalar_t__ Panel_1280x1024x75 ; 
 scalar_t__ Panel_1280x960 ; 
 int RPLLDIV2XO ; 
 int SetCRT2ToDualEdge ; 
 int SetCRT2ToLCD ; 
 int SetCRT2ToRAMDAC ; 
 int SetCRT2ToTV ; 
 int SetInSlaveMode ; 
 int SetLCDDualLink ; 
 int SetSimuScanMode ; 
 int VB_SIS301B ; 
 int VB_SIS301LV ; 
 int VB_SIS302B ; 
 int VB_SIS302LV ; 
 int VB_XGI301C ; 
 int XGI_SetCRT2ToLCDA ; 
 int /*<<< orphan*/  xgifb_reg_and_or (int /*<<< orphan*/ ,int,unsigned short,unsigned char) ; 
 unsigned char xgifb_reg_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xgifb_reg_or (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,int,unsigned char) ; 

__attribute__((used)) static void XGI_SetCRT2ModeRegs(struct vb_device_info *pVBInfo)
{
	unsigned short tempbl;
	short tempcl;

	unsigned char tempah;

	tempah = 0;
	if (!(pVBInfo->VBInfo & DisableCRT2Display)) {
		tempah = xgifb_reg_get(pVBInfo->Part1Port, 0x00);
		tempah &= ~0x10; /* BTRAMDAC */
		tempah |= 0x40; /* BTRAM */

		if (pVBInfo->VBInfo & (SetCRT2ToRAMDAC | SetCRT2ToTV
				| SetCRT2ToLCD)) {
			tempah = 0x40; /* BTDRAM */
			tempcl = pVBInfo->ModeType;
			tempcl -= ModeVGA;
			if (tempcl >= 0) {
				/* BT Color */
				tempah = 0x008 >> tempcl;
				if (tempah == 0)
					tempah = 1;
				tempah |= 0x040;
			}
			if (pVBInfo->VBInfo & SetInSlaveMode)
				tempah ^= 0x50; /* BTDAC */
		}
	}

	xgifb_reg_set(pVBInfo->Part1Port, 0x00, tempah);
	tempah = 0x08;
	tempbl = 0xf0;

	if (pVBInfo->VBInfo & DisableCRT2Display)
		goto reg_and_or;

	tempah = 0x00;
	tempbl = 0xff;

	if (!(pVBInfo->VBInfo & (SetCRT2ToRAMDAC | SetCRT2ToTV |
				 SetCRT2ToLCD | XGI_SetCRT2ToLCDA)))
		goto reg_and_or;

	if ((pVBInfo->VBInfo & XGI_SetCRT2ToLCDA) &&
	    (!(pVBInfo->VBInfo & SetSimuScanMode))) {
		tempbl &= 0xf7;
		tempah |= 0x01;
		goto reg_and_or;
	}

	if (pVBInfo->VBInfo & XGI_SetCRT2ToLCDA) {
		tempbl &= 0xf7;
		tempah |= 0x01;
	}

	if (!(pVBInfo->VBInfo & (SetCRT2ToRAMDAC | SetCRT2ToTV | SetCRT2ToLCD)))
		goto reg_and_or;

	tempbl &= 0xf8;
	tempah = 0x01;

	if (!(pVBInfo->VBInfo & SetInSlaveMode))
		tempah |= 0x02;

	if (!(pVBInfo->VBInfo & SetCRT2ToRAMDAC)) {
		tempah = tempah ^ 0x05;
		if (!(pVBInfo->VBInfo & SetCRT2ToLCD))
			tempah = tempah ^ 0x01;
	}

	if (!(pVBInfo->VBInfo & SetCRT2ToDualEdge))
		tempah |= 0x08;

reg_and_or:
	xgifb_reg_and_or(pVBInfo->Part1Port, 0x2e, tempbl, tempah);

	if (pVBInfo->VBInfo & (SetCRT2ToRAMDAC | SetCRT2ToTV | SetCRT2ToLCD
			| XGI_SetCRT2ToLCDA)) {
		tempah &= (~0x08);
		if ((pVBInfo->ModeType == ModeVGA) && !(pVBInfo->VBInfo
				& SetInSlaveMode)) {
			tempah |= 0x010;
		}
		tempah |= 0x080;

		if (pVBInfo->VBInfo & SetCRT2ToTV) {
			tempah |= 0x020;
			if (pVBInfo->VBInfo & DriverMode)
				tempah = tempah ^ 0x20;
		}

		xgifb_reg_and_or(pVBInfo->Part4Port, 0x0D, ~0x0BF, tempah);
		tempah = 0;

		if (pVBInfo->LCDInfo & SetLCDDualLink)
			tempah |= 0x40;

		if (pVBInfo->VBInfo & SetCRT2ToTV) {
			if (pVBInfo->TVInfo & RPLLDIV2XO)
				tempah |= 0x40;
		}

		if ((pVBInfo->LCDResInfo == Panel_1280x1024) ||
		    (pVBInfo->LCDResInfo == Panel_1280x1024x75))
			tempah |= 0x80;

		if (pVBInfo->LCDResInfo == Panel_1280x960)
			tempah |= 0x80;

		xgifb_reg_set(pVBInfo->Part4Port, 0x0C, tempah);
	}

	if (pVBInfo->VBType & (VB_SIS301B | VB_SIS302B | VB_SIS301LV
			| VB_SIS302LV | VB_XGI301C)) {
		tempah = 0;
		tempbl = 0xfb;

		if (pVBInfo->VBInfo & SetCRT2ToDualEdge) {
			tempbl = 0xff;
			if (pVBInfo->VBInfo & XGI_SetCRT2ToLCDA)
				tempah |= 0x04; /* shampoo 0129 */
		}

		xgifb_reg_and_or(pVBInfo->Part1Port, 0x13, tempbl, tempah);
		tempah = 0x00;
		tempbl = 0xcf;
		if (!(pVBInfo->VBInfo & DisableCRT2Display)) {
			if (pVBInfo->VBInfo & SetCRT2ToDualEdge)
				tempah |= 0x30;
		}

		xgifb_reg_and_or(pVBInfo->Part1Port, 0x2c, tempbl, tempah);
		tempah = 0;
		tempbl = 0x3f;

		if (!(pVBInfo->VBInfo & DisableCRT2Display)) {
			if (pVBInfo->VBInfo & SetCRT2ToDualEdge)
				tempah |= 0xc0;
		}
		xgifb_reg_and_or(pVBInfo->Part4Port, 0x21, tempbl, tempah);
	}

	tempah = 0;
	tempbl = 0x7f;
	if (!(pVBInfo->VBInfo & XGI_SetCRT2ToLCDA)) {
		tempbl = 0xff;
		if (!(pVBInfo->VBInfo & SetCRT2ToDualEdge))
			tempah |= 0x80;
	}

	xgifb_reg_and_or(pVBInfo->Part4Port, 0x23, tempbl, tempah);

	if (pVBInfo->VBType & (VB_SIS302LV | VB_XGI301C)) {
		if (pVBInfo->LCDInfo & SetLCDDualLink) {
			xgifb_reg_or(pVBInfo->Part4Port, 0x27, 0x20);
			xgifb_reg_or(pVBInfo->Part4Port, 0x34, 0x10);
		}
	}
}