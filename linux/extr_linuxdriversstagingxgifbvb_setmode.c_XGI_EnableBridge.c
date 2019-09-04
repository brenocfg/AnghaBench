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
struct xgifb_video_info {int dummy; } ;
struct xgi_hw_device_info {int dummy; } ;
struct vb_device_info {int VBType; int VBInfo; int /*<<< orphan*/  Part1Port; int /*<<< orphan*/  Part4Port; int /*<<< orphan*/  Part2Port; int /*<<< orphan*/  P3c4; } ;

/* Variables and functions */
 int DisableCRT2Display ; 
 int SetCRT2ToDualEdge ; 
 int SetCRT2ToLCD ; 
 int SetCRT2ToRAMDAC ; 
 int SetCRT2ToTV ; 
 int SetInSlaveMode ; 
 int SetSimuScanMode ; 
 int VB_SIS301B ; 
 int VB_SIS301LV ; 
 int VB_SIS302B ; 
 int VB_SIS302LV ; 
 int VB_XGI301C ; 
 int /*<<< orphan*/  XGI_DisableGatingCRT (struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_DisplayOn (struct xgifb_video_info*,struct xgi_hw_device_info*,struct vb_device_info*) ; 
 int XGI_SetCRT2ToLCDA ; 
 int /*<<< orphan*/  xgifb_reg_and (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  xgifb_reg_and_or (int /*<<< orphan*/ ,int,int,int) ; 
 unsigned short xgifb_reg_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xgifb_reg_or (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,int,unsigned short) ; 

__attribute__((used)) static void XGI_EnableBridge(struct xgifb_video_info *xgifb_info,
			     struct xgi_hw_device_info *HwDeviceExtension,
			     struct vb_device_info *pVBInfo)
{
	unsigned short tempah;

	if (pVBInfo->VBType & (VB_SIS301B | VB_SIS302B | VB_SIS301LV
			| VB_SIS302LV | VB_XGI301C)) {
		if (pVBInfo->VBInfo & SetCRT2ToDualEdge)
			/* Power on */
			xgifb_reg_set(pVBInfo->Part1Port, 0x1E, 0x20);

		if (pVBInfo->VBInfo & (SetCRT2ToLCD | SetCRT2ToTV |
				       SetCRT2ToRAMDAC)) {
			tempah = xgifb_reg_get(pVBInfo->P3c4, 0x32);
			tempah &= 0xDF;
			if (pVBInfo->VBInfo & SetInSlaveMode) {
				if (!(pVBInfo->VBInfo & SetCRT2ToRAMDAC))
					tempah |= 0x20;
			}
			xgifb_reg_set(pVBInfo->P3c4, 0x32, tempah);
			xgifb_reg_or(pVBInfo->P3c4, 0x1E, 0x20);

			tempah = xgifb_reg_get(pVBInfo->Part1Port, 0x2E);

			if (!(tempah & 0x80))
				xgifb_reg_or(pVBInfo->Part1Port, 0x2E, 0x80);
			xgifb_reg_and(pVBInfo->Part1Port, 0x00, 0x7F);
		}

		if (!(pVBInfo->VBInfo & DisableCRT2Display)) {
			xgifb_reg_and_or(pVBInfo->Part2Port, 0x00, ~0xE0,
					 0x20); /* shampoo 0129 */
			if (pVBInfo->VBType & (VB_SIS302LV | VB_XGI301C)) {
				if (pVBInfo->VBInfo &
					(SetCRT2ToLCD | XGI_SetCRT2ToLCDA))
					 /* LVDS PLL power on */
					xgifb_reg_and(pVBInfo->Part4Port, 0x2A,
						      0x7F);
				/* LVDS Driver power on */
				xgifb_reg_and(pVBInfo->Part4Port, 0x30, 0x7F);
			}
		}

		tempah = 0x00;

		if (!(pVBInfo->VBInfo & DisableCRT2Display)) {
			tempah = 0xc0;

			if (!(pVBInfo->VBInfo & SetSimuScanMode) &&
			    (pVBInfo->VBInfo & XGI_SetCRT2ToLCDA) &&
			    (pVBInfo->VBInfo & SetCRT2ToDualEdge)) {
				tempah = tempah & 0x40;
				if (pVBInfo->VBInfo & XGI_SetCRT2ToLCDA)
					tempah = tempah ^ 0xC0;
			}
		}

		/* EnablePart4_1F */
		xgifb_reg_or(pVBInfo->Part4Port, 0x1F, tempah);

		XGI_DisableGatingCRT(pVBInfo);
		XGI_DisplayOn(xgifb_info, HwDeviceExtension, pVBInfo);
	} /* 301 */
	else { /* LVDS */
		if (pVBInfo->VBInfo & (SetCRT2ToTV | SetCRT2ToLCD
				| XGI_SetCRT2ToLCDA))
			/* enable CRT2 */
			xgifb_reg_or(pVBInfo->Part1Port, 0x1E, 0x20);

		tempah = xgifb_reg_get(pVBInfo->Part1Port, 0x2E);
		if (!(tempah & 0x80))
			xgifb_reg_or(pVBInfo->Part1Port, 0x2E, 0x80);

		xgifb_reg_and(pVBInfo->Part1Port, 0x00, 0x7F);
		XGI_DisplayOn(xgifb_info, HwDeviceExtension, pVBInfo);
	} /* End of VB */
}