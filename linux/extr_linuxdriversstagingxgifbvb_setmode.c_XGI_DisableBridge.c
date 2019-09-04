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
struct vb_device_info {int VBType; int VBInfo; int /*<<< orphan*/  P3c4; int /*<<< orphan*/  Part1Port; int /*<<< orphan*/  Part2Port; int /*<<< orphan*/  Part4Port; } ;

/* Variables and functions */
 int DisableCRT2Display ; 
 int SetCRT2ToDualEdge ; 
 int SetCRT2ToLCD ; 
 int SetCRT2ToRAMDAC ; 
 int SetCRT2ToTV ; 
 int SetSimuScanMode ; 
 int VB_SIS301B ; 
 int VB_SIS301LV ; 
 int VB_SIS302B ; 
 int VB_SIS302LV ; 
 int VB_XGI301C ; 
 int /*<<< orphan*/  XGI_DisplayOff (struct xgifb_video_info*,struct xgi_hw_device_info*,struct vb_device_info*) ; 
 scalar_t__ XGI_IsLCDON (struct vb_device_info*) ; 
 int XGI_SetCRT2ToLCDA ; 
 int /*<<< orphan*/  xgifb_reg_and (int /*<<< orphan*/ ,int,int) ; 
 unsigned short xgifb_reg_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xgifb_reg_or (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,int,unsigned short) ; 

__attribute__((used)) static void XGI_DisableBridge(struct xgifb_video_info *xgifb_info,
			      struct xgi_hw_device_info *HwDeviceExtension,
			      struct vb_device_info *pVBInfo)
{
	unsigned short tempah = 0;

	if (pVBInfo->VBType & (VB_SIS301B | VB_SIS302B | VB_SIS301LV
			| VB_SIS302LV | VB_XGI301C)) {
		tempah = 0x3F;
		if (!(pVBInfo->VBInfo &
		    (DisableCRT2Display | SetSimuScanMode))) {
			if (pVBInfo->VBInfo & XGI_SetCRT2ToLCDA) {
				if (pVBInfo->VBInfo & SetCRT2ToDualEdge)
					tempah = 0x7F; /* Disable Channel A */
			}
		}

		/* disable part4_1f */
		xgifb_reg_and(pVBInfo->Part4Port, 0x1F, tempah);

		if (pVBInfo->VBType & (VB_SIS302LV | VB_XGI301C)) {
			if (((pVBInfo->VBInfo &
			      (SetCRT2ToLCD | XGI_SetCRT2ToLCDA))) ||
				(XGI_IsLCDON(pVBInfo)))
				/* LVDS Driver power down */
				xgifb_reg_or(pVBInfo->Part4Port, 0x30, 0x80);
		}

		if (pVBInfo->VBInfo & (DisableCRT2Display | XGI_SetCRT2ToLCDA |
				       SetSimuScanMode))
			XGI_DisplayOff(xgifb_info, HwDeviceExtension, pVBInfo);

		if (pVBInfo->VBInfo & XGI_SetCRT2ToLCDA)
			/* Power down */
			xgifb_reg_and(pVBInfo->Part1Port, 0x1e, 0xdf);

		/* disable TV as primary VGA swap */
		xgifb_reg_and(pVBInfo->P3c4, 0x32, 0xdf);

		if ((pVBInfo->VBInfo & (SetSimuScanMode | SetCRT2ToDualEdge)))
			xgifb_reg_and(pVBInfo->Part2Port, 0x00, 0xdf);

		if ((pVBInfo->VBInfo &
			(DisableCRT2Display | SetSimuScanMode)) ||
		    (!(pVBInfo->VBInfo & XGI_SetCRT2ToLCDA) &&
		    (pVBInfo->VBInfo &
			(SetCRT2ToRAMDAC | SetCRT2ToLCD | SetCRT2ToTV))))
			xgifb_reg_or(pVBInfo->Part1Port, 0x00, 0x80);

		if ((pVBInfo->VBInfo &
			(DisableCRT2Display | SetSimuScanMode)) ||
		    (!(pVBInfo->VBInfo & XGI_SetCRT2ToLCDA)) ||
		    (pVBInfo->VBInfo &
			(SetCRT2ToRAMDAC | SetCRT2ToLCD | SetCRT2ToTV))) {
			/* save Part1 index 0 */
			tempah = xgifb_reg_get(pVBInfo->Part1Port, 0x00);
			/* BTDAC = 1, avoid VB reset */
			xgifb_reg_or(pVBInfo->Part1Port, 0x00, 0x10);
			/* disable CRT2 */
			xgifb_reg_and(pVBInfo->Part1Port, 0x1E, 0xDF);
			/* restore Part1 index 0 */
			xgifb_reg_set(pVBInfo->Part1Port, 0x00, tempah);
		}
	} else { /* {301} */
		if (pVBInfo->VBInfo & (SetCRT2ToLCD | SetCRT2ToTV)) {
			xgifb_reg_or(pVBInfo->Part1Port, 0x00, 0x80);
			/* Disable CRT2 */
			xgifb_reg_and(pVBInfo->Part1Port, 0x1E, 0xDF);
			/* Disable TV asPrimary VGA swap */
			xgifb_reg_and(pVBInfo->P3c4, 0x32, 0xDF);
		}

		if (pVBInfo->VBInfo & (DisableCRT2Display | XGI_SetCRT2ToLCDA
				| SetSimuScanMode))
			XGI_DisplayOff(xgifb_info, HwDeviceExtension, pVBInfo);
	}
}