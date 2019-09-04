#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xgi_hw_device_info {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * data; } ;
struct TYPE_3__ {int /*<<< orphan*/ * data; } ;
struct vb_device_info {int VBInfo; TYPE_2__ TimingV; TYPE_1__ TimingH; } ;
struct XGI_LVDSCRT1VDataStruct {int /*<<< orphan*/ * Reg; } ;
struct XGI_LVDSCRT1HDataStruct {int /*<<< orphan*/ * Reg; } ;

/* Variables and functions */
 int SetCRT2ToLCD ; 
 void* XGI_GetLcdPtr (int /*<<< orphan*/ ,unsigned short,struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_SetCRT1Timing_H (struct vb_device_info*,struct xgi_hw_device_info*) ; 
 int /*<<< orphan*/  XGI_SetCRT1Timing_V (unsigned short,struct vb_device_info*) ; 
 int XGI_SetCRT2ToLCDA ; 
 int /*<<< orphan*/  xgifb_epllcd_crt1_h ; 
 int /*<<< orphan*/  xgifb_epllcd_crt1_v ; 

__attribute__((used)) static void XGI_ModCRT1Regs(unsigned short ModeIdIndex,
			    struct xgi_hw_device_info *HwDeviceExtension,
			    struct vb_device_info *pVBInfo)
{
	unsigned short i;
	struct XGI_LVDSCRT1HDataStruct const *LCDPtr = NULL;
	struct XGI_LVDSCRT1VDataStruct const *LCDPtr1 = NULL;

	if (pVBInfo->VBInfo & (SetCRT2ToLCD | XGI_SetCRT2ToLCDA)) {
		LCDPtr = XGI_GetLcdPtr(xgifb_epllcd_crt1_h, ModeIdIndex,
				       pVBInfo);

		for (i = 0; i < 8; i++)
			pVBInfo->TimingH.data[i] = LCDPtr[0].Reg[i];
	}

	XGI_SetCRT1Timing_H(pVBInfo, HwDeviceExtension);

	if (pVBInfo->VBInfo & (SetCRT2ToLCD | XGI_SetCRT2ToLCDA)) {
		LCDPtr1 = XGI_GetLcdPtr(xgifb_epllcd_crt1_v, ModeIdIndex,
					pVBInfo);
		for (i = 0; i < 7; i++)
			pVBInfo->TimingV.data[i] = LCDPtr1[0].Reg[i];
	}

	XGI_SetCRT1Timing_V(ModeIdIndex, pVBInfo);
}