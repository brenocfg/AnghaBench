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
struct xgi_hw_device_info {int dummy; } ;
struct vb_device_info {int SelectCRT2Rate; int /*<<< orphan*/  SetFlag; } ;

/* Variables and functions */
 int /*<<< orphan*/  ProgrammingCRT2 ; 
 int /*<<< orphan*/  XGI_AutoThreshold (struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_GetCRT2Data (unsigned short,unsigned short,struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_GetCRT2ResInfo (unsigned short,struct vb_device_info*) ; 
 unsigned short XGI_GetRatePtrCRT2 (struct xgi_hw_device_info*,unsigned short,unsigned short,struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_PreSetGroup1 (unsigned short,unsigned short,unsigned short,struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_SaveCRT2Info (unsigned short,struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_SearchModeID (unsigned short,unsigned short*) ; 
 int /*<<< orphan*/  XGI_SetCRT2VCLK (unsigned short,unsigned short,struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_SetGroup1 (unsigned short,unsigned short,struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_SetGroup2 (unsigned short,unsigned short,struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_SetGroup3 (unsigned short,struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_SetGroup4 (unsigned short,unsigned short,struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_SetGroup5 (struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_SetLCDRegs (unsigned short,struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_SetLockRegs (unsigned short,unsigned short,struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_SetTap4Regs (struct vb_device_info*) ; 

__attribute__((used)) static unsigned char XGI_SetCRT2Group301(unsigned short ModeNo,
					 struct xgi_hw_device_info *HwDeviceExtension,
					 struct vb_device_info *pVBInfo)
{
	unsigned short ModeIdIndex, RefreshRateTableIndex;

	pVBInfo->SetFlag |= ProgrammingCRT2;
	XGI_SearchModeID(ModeNo, &ModeIdIndex);
	pVBInfo->SelectCRT2Rate = 4;
	RefreshRateTableIndex = XGI_GetRatePtrCRT2(HwDeviceExtension, ModeNo,
						   ModeIdIndex, pVBInfo);
	XGI_SaveCRT2Info(ModeNo, pVBInfo);
	XGI_GetCRT2ResInfo(ModeIdIndex, pVBInfo);
	XGI_GetCRT2Data(ModeIdIndex, RefreshRateTableIndex, pVBInfo);
	XGI_PreSetGroup1(ModeNo, ModeIdIndex, RefreshRateTableIndex, pVBInfo);
	XGI_SetGroup1(ModeIdIndex, RefreshRateTableIndex, pVBInfo);
	XGI_SetLockRegs(ModeNo, ModeIdIndex, pVBInfo);
	XGI_SetGroup2(ModeNo, ModeIdIndex, pVBInfo);
	XGI_SetLCDRegs(ModeIdIndex, pVBInfo);
	XGI_SetTap4Regs(pVBInfo);
	XGI_SetGroup3(ModeIdIndex, pVBInfo);
	XGI_SetGroup4(ModeIdIndex, RefreshRateTableIndex, pVBInfo);
	XGI_SetCRT2VCLK(ModeIdIndex, RefreshRateTableIndex, pVBInfo);
	XGI_SetGroup5(pVBInfo);
	XGI_AutoThreshold(pVBInfo);
	return 1;
}