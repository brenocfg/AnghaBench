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
struct xgi_hw_device_info {int /*<<< orphan*/  jChipType; } ;
struct vb_device_info {int dummy; } ;
struct TYPE_4__ {unsigned short Ext_CRTVCLK; } ;
struct TYPE_3__ {int CLOCK; } ;

/* Variables and functions */
 int /*<<< orphan*/  InitTo330Pointer (int /*<<< orphan*/ ,struct vb_device_info*) ; 
 TYPE_2__* XGI330_RefIndex ; 
 unsigned short XGI_GetRatePtrCRT2 (struct xgi_hw_device_info*,unsigned short,unsigned short,struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_SearchModeID (unsigned short,unsigned short*) ; 
 TYPE_1__* XGI_VCLKData ; 

__attribute__((used)) static int XGIfb_mode_rate_to_dclock(struct vb_device_info *XGI_Pr,
				     struct xgi_hw_device_info *HwDeviceExtension,
				     unsigned char modeno)
{
	unsigned short ModeNo = modeno;
	unsigned short ModeIdIndex = 0, ClockIndex = 0;
	unsigned short RefreshRateTableIndex = 0;

	InitTo330Pointer(HwDeviceExtension->jChipType, XGI_Pr);

	XGI_SearchModeID(ModeNo, &ModeIdIndex);

	RefreshRateTableIndex = XGI_GetRatePtrCRT2(HwDeviceExtension, ModeNo,
						   ModeIdIndex, XGI_Pr);

	ClockIndex = XGI330_RefIndex[RefreshRateTableIndex].Ext_CRTVCLK;

	return XGI_VCLKData[ClockIndex].CLOCK * 1000;
}