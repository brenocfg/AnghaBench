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
struct xgi_hw_device_info {scalar_t__ jChipType; } ;
struct vb_device_info {int /*<<< orphan*/  P3c4; } ;
struct TYPE_4__ {unsigned char Ext_CRTVCLK; } ;
struct TYPE_3__ {short CLOCK; } ;

/* Variables and functions */
 unsigned char IndexMask ; 
 scalar_t__ XG20 ; 
 scalar_t__ XG27 ; 
 TYPE_2__* XGI330_RefIndex ; 
 TYPE_1__* XGI_VCLKData ; 
 int /*<<< orphan*/  xgifb_reg_and_or (int /*<<< orphan*/ ,int,int,unsigned short) ; 
 unsigned short xgifb_reg_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,int,unsigned short) ; 

__attribute__((used)) static void XGI_SetVCLKState(struct xgi_hw_device_info *HwDeviceExtension,
			     unsigned short RefreshRateTableIndex,
			     struct vb_device_info *pVBInfo)
{
	unsigned short data, data2 = 0;
	short VCLK;

	unsigned char index;

	index = XGI330_RefIndex[RefreshRateTableIndex].Ext_CRTVCLK;
	index &= IndexMask;
	VCLK = XGI_VCLKData[index].CLOCK;

	data = xgifb_reg_get(pVBInfo->P3c4, 0x32);
	data &= 0xf3;
	if (VCLK >= 200)
		data |= 0x0c; /* VCLK > 200 */

	if (HwDeviceExtension->jChipType >= XG20)
		data &= ~0x04; /* 2 pixel mode */

	xgifb_reg_set(pVBInfo->P3c4, 0x32, data);

	if (HwDeviceExtension->jChipType < XG20) {
		data = xgifb_reg_get(pVBInfo->P3c4, 0x1F);
		data &= 0xE7;
		if (VCLK < 200)
			data |= 0x10;
		xgifb_reg_set(pVBInfo->P3c4, 0x1F, data);
	}

	data2 = 0x00;

	xgifb_reg_and_or(pVBInfo->P3c4, 0x07, 0xFC, data2);
	if (HwDeviceExtension->jChipType >= XG27)
		xgifb_reg_and_or(pVBInfo->P3c4, 0x40, 0xFC, data2 & 0x03);
}