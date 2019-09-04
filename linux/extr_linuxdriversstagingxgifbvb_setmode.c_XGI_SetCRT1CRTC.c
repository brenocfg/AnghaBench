#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct xgi_hw_device_info {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/ * data; } ;
struct TYPE_5__ {int /*<<< orphan*/ * data; } ;
struct vb_device_info {int ModeType; int /*<<< orphan*/  P3d4; TYPE_2__ TimingV; TYPE_1__ TimingH; } ;
struct TYPE_8__ {unsigned char Ext_CRT1CRTC; } ;
struct TYPE_7__ {int /*<<< orphan*/ * CR; } ;

/* Variables and functions */
 unsigned char IndexMask ; 
 TYPE_4__* XGI330_RefIndex ; 
 TYPE_3__* XGI_CRT1Table ; 
 int /*<<< orphan*/  XGI_SetCRT1Timing_H (struct vb_device_info*,struct xgi_hw_device_info*) ; 
 int /*<<< orphan*/  XGI_SetCRT1Timing_V (unsigned short,struct vb_device_info*) ; 
 unsigned char xgifb_reg_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void XGI_SetCRT1CRTC(unsigned short ModeIdIndex,
			    unsigned short RefreshRateTableIndex,
			    struct vb_device_info *pVBInfo,
			    struct xgi_hw_device_info *HwDeviceExtension)
{
	unsigned char index, data;
	unsigned short i;

	/* Get index */
	index = XGI330_RefIndex[RefreshRateTableIndex].Ext_CRT1CRTC;
	index = index & IndexMask;

	data = xgifb_reg_get(pVBInfo->P3d4, 0x11);
	data &= 0x7F;
	xgifb_reg_set(pVBInfo->P3d4, 0x11, data); /* Unlock CRTC */

	for (i = 0; i < 8; i++)
		pVBInfo->TimingH.data[i]
				= XGI_CRT1Table[index].CR[i];

	for (i = 0; i < 7; i++)
		pVBInfo->TimingV.data[i]
				= XGI_CRT1Table[index].CR[i + 8];

	XGI_SetCRT1Timing_H(pVBInfo, HwDeviceExtension);

	XGI_SetCRT1Timing_V(ModeIdIndex, pVBInfo);

	if (pVBInfo->ModeType > 0x03)
		xgifb_reg_set(pVBInfo->P3d4, 0x14, 0x4F);
}