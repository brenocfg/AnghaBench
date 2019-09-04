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
struct xgi_hw_device_info {int /*<<< orphan*/  pjVideoMemoryAddress; } ;
struct vb_device_info {int /*<<< orphan*/  P3c4; int /*<<< orphan*/  FBAddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  XGINew_DDRSizing340 (struct xgi_hw_device_info*,struct vb_device_info*) ; 
 int /*<<< orphan*/  XGISetModeNew (struct xgifb_video_info*,struct xgi_hw_device_info*,int) ; 
 int /*<<< orphan*/  XGI_DisplayOff (struct xgifb_video_info*,struct xgi_hw_device_info*,struct vb_device_info*) ; 
 unsigned short xgifb_reg_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,int,unsigned short) ; 

__attribute__((used)) static void XGINew_SetDRAMSize_340(struct xgifb_video_info *xgifb_info,
				   struct xgi_hw_device_info *HwDeviceExtension,
				   struct vb_device_info *pVBInfo)
{
	unsigned short data;

	pVBInfo->FBAddr = HwDeviceExtension->pjVideoMemoryAddress;

	XGISetModeNew(xgifb_info, HwDeviceExtension, 0x2e);

	data = xgifb_reg_get(pVBInfo->P3c4, 0x21);
	/* disable read cache */
	xgifb_reg_set(pVBInfo->P3c4, 0x21, (unsigned short)(data & 0xDF));
	XGI_DisplayOff(xgifb_info, HwDeviceExtension, pVBInfo);

	XGINew_DDRSizing340(HwDeviceExtension, pVBInfo);
	data = xgifb_reg_get(pVBInfo->P3c4, 0x21);
	/* enable read cache */
	xgifb_reg_set(pVBInfo->P3c4, 0x21, (unsigned short)(data | 0x20));
}