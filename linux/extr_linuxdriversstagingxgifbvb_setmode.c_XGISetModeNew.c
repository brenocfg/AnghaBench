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
struct xgifb_video_info {int /*<<< orphan*/  vga_base; } ;
struct xgi_hw_device_info {scalar_t__ jChipType; int ujVBChipID; } ;
struct vb_device_info {int IF_DEF_LVDS; int VBInfo; int ModeType; scalar_t__ SetFlag; int /*<<< orphan*/  P3c4; int /*<<< orphan*/  P3d4; scalar_t__ VBType; } ;
struct TYPE_2__ {int Ext_ModeFlag; } ;

/* Variables and functions */
 int DisableCRT2Display ; 
 int /*<<< orphan*/  InitTo330Pointer (scalar_t__,struct vb_device_info*) ; 
 int ModeTypeMask ; 
 int SetSimuScanMode ; 
 int SwitchCRT2 ; 
#define  VB_CHIP_301 129 
#define  VB_CHIP_302 128 
 scalar_t__ XG20 ; 
 scalar_t__ XG21 ; 
 scalar_t__ XG27 ; 
 TYPE_1__* XGI330_EModeIDTable ; 
 int /*<<< orphan*/  XGIRegInit (struct vb_device_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XGI_DisableBridge (struct xgifb_video_info*,struct xgi_hw_device_info*,struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_DisplayOff (struct xgifb_video_info*,struct xgi_hw_device_info*,struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_DisplayOn (struct xgifb_video_info*,struct xgi_hw_device_info*,struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_EnableBridge (struct xgifb_video_info*,struct xgi_hw_device_info*,struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_GetLCDInfo (unsigned short,struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_GetTVInfo (unsigned short,struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_GetVBInfo (unsigned short,struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_LockCRT2 (struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_OEM310Setting (unsigned short,struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_SearchModeID (unsigned short,unsigned short*) ; 
 int /*<<< orphan*/  XGI_SetCRT1Group (struct xgifb_video_info*,struct xgi_hw_device_info*,unsigned short,unsigned short,struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_SetCRT2Group301 (unsigned short,struct xgi_hw_device_info*,struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_SetCRT2ModeRegs (struct vb_device_info*) ; 
 int XGI_SetCRT2ToLCDA ; 
 int /*<<< orphan*/  XGI_SetLCDAGroup (unsigned short,unsigned short,struct xgi_hw_device_info*,struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_UnLockCRT2 (struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_UpdateModeInfo (struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_XG21CheckLVDSMode (struct xgifb_video_info*,unsigned short,unsigned short) ; 
 int xgifb_reg_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,int,int) ; 

unsigned char XGISetModeNew(struct xgifb_video_info *xgifb_info,
			    struct xgi_hw_device_info *HwDeviceExtension,
			    unsigned short ModeNo)
{
	unsigned short ModeIdIndex;
	struct vb_device_info VBINF;
	struct vb_device_info *pVBInfo = &VBINF;

	pVBInfo->IF_DEF_LVDS = 0;

	if (HwDeviceExtension->jChipType >= XG20)
		pVBInfo->VBType = 0; /* set VBType default 0 */

	XGIRegInit(pVBInfo, xgifb_info->vga_base);

	/* for x86 Linux, XG21 LVDS */
	if (HwDeviceExtension->jChipType == XG21) {
		if ((xgifb_reg_get(pVBInfo->P3d4, 0x38) & 0xE0) == 0xC0)
			pVBInfo->IF_DEF_LVDS = 1;
	}
	if (HwDeviceExtension->jChipType == XG27) {
		if ((xgifb_reg_get(pVBInfo->P3d4, 0x38) & 0xE0) == 0xC0) {
			if (xgifb_reg_get(pVBInfo->P3d4, 0x30) & 0x20)
				pVBInfo->IF_DEF_LVDS = 1;
		}
	}

	InitTo330Pointer(HwDeviceExtension->jChipType, pVBInfo);
	if (ModeNo & 0x80)
		ModeNo = ModeNo & 0x7F;
	xgifb_reg_set(pVBInfo->P3c4, 0x05, 0x86);

	if (HwDeviceExtension->jChipType < XG20)
		XGI_UnLockCRT2(pVBInfo);

	XGI_SearchModeID(ModeNo, &ModeIdIndex);

	if (HwDeviceExtension->jChipType < XG20) {
		XGI_GetVBInfo(ModeIdIndex, pVBInfo);
		XGI_GetTVInfo(ModeIdIndex, pVBInfo);
		XGI_GetLCDInfo(ModeIdIndex, pVBInfo);
		XGI_DisableBridge(xgifb_info, HwDeviceExtension, pVBInfo);

		if (pVBInfo->VBInfo & (SetSimuScanMode | XGI_SetCRT2ToLCDA) ||
		    !(pVBInfo->VBInfo & SwitchCRT2)) {
			XGI_SetCRT1Group(xgifb_info, HwDeviceExtension, ModeNo,
					 ModeIdIndex, pVBInfo);

			if (pVBInfo->VBInfo & XGI_SetCRT2ToLCDA) {
				XGI_SetLCDAGroup(ModeNo, ModeIdIndex,
						 HwDeviceExtension, pVBInfo);
			}
		}

		if (pVBInfo->VBInfo & (SetSimuScanMode | SwitchCRT2)) {
			switch (HwDeviceExtension->ujVBChipID) {
			case VB_CHIP_301: /* fall through */
			case VB_CHIP_302:
				/* add for CRT2 */
				XGI_SetCRT2Group301(ModeNo, HwDeviceExtension,
						    pVBInfo);
				break;

			default:
				break;
			}
		}

		XGI_SetCRT2ModeRegs(pVBInfo);
		XGI_OEM310Setting(ModeIdIndex, pVBInfo); /* 0212 */
		XGI_EnableBridge(xgifb_info, HwDeviceExtension, pVBInfo);
	} /* !XG20 */
	else {
		if (pVBInfo->IF_DEF_LVDS == 1)
			if (!XGI_XG21CheckLVDSMode(xgifb_info, ModeNo,
						   ModeIdIndex))
				return 0;

		pVBInfo->ModeType =
			XGI330_EModeIDTable[ModeIdIndex].Ext_ModeFlag
			& ModeTypeMask;

		pVBInfo->SetFlag = 0;
		pVBInfo->VBInfo = DisableCRT2Display;

		XGI_DisplayOff(xgifb_info, HwDeviceExtension, pVBInfo);

		XGI_SetCRT1Group(xgifb_info, HwDeviceExtension, ModeNo,
				 ModeIdIndex, pVBInfo);

		XGI_DisplayOn(xgifb_info, HwDeviceExtension, pVBInfo);
	}

	XGI_UpdateModeInfo(pVBInfo);

	if (HwDeviceExtension->jChipType < XG20)
		XGI_LockCRT2(pVBInfo);

	return 1;
}