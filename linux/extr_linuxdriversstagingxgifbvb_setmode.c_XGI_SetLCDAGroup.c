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
struct vb_device_info {int /*<<< orphan*/  SetFlag; } ;

/* Variables and functions */
 int /*<<< orphan*/  ProgrammingCRT2 ; 
 int /*<<< orphan*/  XGI_GetLVDSData (unsigned short,struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_GetLVDSResInfo (unsigned short,struct vb_device_info*) ; 
 unsigned short XGI_GetRatePtrCRT2 (struct xgi_hw_device_info*,unsigned short,unsigned short,struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_ModCRT1Regs (unsigned short,struct xgi_hw_device_info*,struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_SetCRT2ECLK (unsigned short,unsigned short,struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_SetLVDSRegs (unsigned short,struct vb_device_info*) ; 

__attribute__((used)) static void XGI_SetLCDAGroup(unsigned short ModeNo, unsigned short ModeIdIndex,
			     struct xgi_hw_device_info *HwDeviceExtension,
			     struct vb_device_info *pVBInfo)
{
	unsigned short RefreshRateTableIndex;

	pVBInfo->SetFlag |= ProgrammingCRT2;
	RefreshRateTableIndex = XGI_GetRatePtrCRT2(HwDeviceExtension, ModeNo,
						   ModeIdIndex, pVBInfo);
	XGI_GetLVDSResInfo(ModeIdIndex, pVBInfo);
	XGI_GetLVDSData(ModeIdIndex, pVBInfo);
	XGI_ModCRT1Regs(ModeIdIndex, HwDeviceExtension, pVBInfo);
	XGI_SetLVDSRegs(ModeIdIndex, pVBInfo);
	XGI_SetCRT2ECLK(ModeIdIndex, RefreshRateTableIndex, pVBInfo);
}