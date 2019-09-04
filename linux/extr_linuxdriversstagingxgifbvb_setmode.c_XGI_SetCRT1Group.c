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
struct xgifb_video_info {int dummy; } ;
struct xgi_hw_device_info {scalar_t__ jChipType; } ;
struct vb_device_info {scalar_t__ IF_DEF_LVDS; unsigned short SetFlag; int VBType; int VBInfo; int /*<<< orphan*/  P3d4; scalar_t__ SelectCRT2Rate; int /*<<< orphan*/  P3c2; } ;
struct TYPE_2__ {int /*<<< orphan*/  MISC; } ;

/* Variables and functions */
 unsigned short ProgrammingCRT2 ; 
 int SetInSlaveMode ; 
 int SetSimuScanMode ; 
 int VB_SIS301B ; 
 int VB_SIS301LV ; 
 int VB_SIS302B ; 
 int VB_SIS302LV ; 
 int VB_XGI301C ; 
 scalar_t__ XG21 ; 
 scalar_t__ XG27 ; 
 TYPE_1__ XGI330_StandTable ; 
 int /*<<< orphan*/  XGI_ClearExt1Regs (struct vb_device_info*) ; 
 unsigned short XGI_GetRatePtrCRT2 (struct xgi_hw_device_info*,unsigned short,unsigned short,struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_LoadDAC (struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_SetATTRegs (unsigned short,struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_SetCRT1CRTC (unsigned short,unsigned short,struct vb_device_info*,struct xgi_hw_device_info*) ; 
 int /*<<< orphan*/  XGI_SetCRT1DE (unsigned short,unsigned short,struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_SetCRT1FIFO (struct xgi_hw_device_info*,struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_SetCRT1ModeRegs (struct xgi_hw_device_info*,unsigned short,unsigned short,struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_SetCRT1Offset (unsigned short,unsigned short,unsigned short,struct xgi_hw_device_info*,struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_SetCRT1VCLK (unsigned short,struct xgi_hw_device_info*,unsigned short,struct vb_device_info*) ; 
 int XGI_SetCRT2ToLCDA ; 
 int /*<<< orphan*/  XGI_SetCRTCRegs (struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_SetDefaultVCLK (struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_SetGRCRegs (struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_SetSeqRegs (struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_SetSync (unsigned short,struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_SetXG21CRTC (unsigned short,struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_SetXG27CRTC (unsigned short,struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_UpdateXG21CRTC (unsigned short,struct vb_device_info*,unsigned short) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned short xgifb_reg_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xgifb_set_lcd (scalar_t__,struct vb_device_info*,unsigned short) ; 
 int /*<<< orphan*/  xgifb_set_lvds (struct xgifb_video_info*,scalar_t__,unsigned short,struct vb_device_info*) ; 

__attribute__((used)) static void XGI_SetCRT1Group(struct xgifb_video_info *xgifb_info,
			     struct xgi_hw_device_info *HwDeviceExtension,
			     unsigned short ModeNo, unsigned short ModeIdIndex,
			     struct vb_device_info *pVBInfo)
{
	unsigned short RefreshRateTableIndex, temp;

	XGI_SetSeqRegs(pVBInfo);
	outb(XGI330_StandTable.MISC, pVBInfo->P3c2);
	XGI_SetCRTCRegs(pVBInfo);
	XGI_SetATTRegs(ModeIdIndex, pVBInfo);
	XGI_SetGRCRegs(pVBInfo);
	XGI_ClearExt1Regs(pVBInfo);

	if (HwDeviceExtension->jChipType == XG27) {
		if (pVBInfo->IF_DEF_LVDS == 0)
			XGI_SetDefaultVCLK(pVBInfo);
	}

	temp = ~ProgrammingCRT2;
	pVBInfo->SetFlag &= temp;
	pVBInfo->SelectCRT2Rate = 0;

	if (pVBInfo->VBType & (VB_SIS301B | VB_SIS302B | VB_SIS301LV
			| VB_SIS302LV | VB_XGI301C)) {
		if (pVBInfo->VBInfo & (SetSimuScanMode | XGI_SetCRT2ToLCDA
				| SetInSlaveMode)) {
			pVBInfo->SetFlag |= ProgrammingCRT2;
		}
	}

	RefreshRateTableIndex = XGI_GetRatePtrCRT2(HwDeviceExtension, ModeNo,
						   ModeIdIndex, pVBInfo);
	if (RefreshRateTableIndex != 0xFFFF) {
		XGI_SetSync(RefreshRateTableIndex, pVBInfo);
		XGI_SetCRT1CRTC(ModeIdIndex, RefreshRateTableIndex,
				pVBInfo, HwDeviceExtension);
		XGI_SetCRT1DE(ModeIdIndex, RefreshRateTableIndex, pVBInfo);
		XGI_SetCRT1Offset(ModeNo, ModeIdIndex, RefreshRateTableIndex,
				  HwDeviceExtension, pVBInfo);
		XGI_SetCRT1VCLK(ModeIdIndex, HwDeviceExtension,
				RefreshRateTableIndex, pVBInfo);
	}

	if (HwDeviceExtension->jChipType >= XG21) {
		temp = xgifb_reg_get(pVBInfo->P3d4, 0x38);
		if (temp & 0xA0) {
			if (HwDeviceExtension->jChipType == XG27)
				XGI_SetXG27CRTC(RefreshRateTableIndex, pVBInfo);
			else
				XGI_SetXG21CRTC(RefreshRateTableIndex, pVBInfo);

			XGI_UpdateXG21CRTC(ModeNo, pVBInfo,
					   RefreshRateTableIndex);

			xgifb_set_lcd(HwDeviceExtension->jChipType,
				      pVBInfo, RefreshRateTableIndex);

			if (pVBInfo->IF_DEF_LVDS == 1)
				xgifb_set_lvds(xgifb_info,
					       HwDeviceExtension->jChipType,
					       ModeIdIndex, pVBInfo);
		}
	}

	pVBInfo->SetFlag &= (~ProgrammingCRT2);
	XGI_SetCRT1FIFO(HwDeviceExtension, pVBInfo);
	XGI_SetCRT1ModeRegs(HwDeviceExtension, ModeIdIndex,
			    RefreshRateTableIndex, pVBInfo);
	XGI_LoadDAC(pVBInfo);
}