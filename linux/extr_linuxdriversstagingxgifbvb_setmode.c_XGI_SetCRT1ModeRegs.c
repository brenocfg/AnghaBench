#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xgi_hw_device_info {scalar_t__ jChipType; } ;
struct vb_device_info {unsigned short ModeType; int /*<<< orphan*/  P3d4; int /*<<< orphan*/  P3c4; } ;
struct TYPE_6__ {unsigned short Ext_ModeFlag; unsigned short Ext_RESINFO; } ;
struct TYPE_5__ {unsigned short HTotal; } ;
struct TYPE_4__ {unsigned short Ext_InfoFlag; } ;

/* Variables and functions */
 unsigned short HalfDCLK ; 
 unsigned short InterlaceMode ; 
 unsigned short LineCompareOff ; 
 unsigned short ModeVGA ; 
 scalar_t__ XG20 ; 
 scalar_t__ XG27 ; 
 TYPE_3__* XGI330_EModeIDTable ; 
 TYPE_2__* XGI330_ModeResInfo ; 
 TYPE_1__* XGI330_RefIndex ; 
 int /*<<< orphan*/  XGI_SetVCLKState (struct xgi_hw_device_info*,unsigned short,struct vb_device_info*) ; 
 int /*<<< orphan*/  xgifb_reg_and_or (int /*<<< orphan*/ ,int,int,unsigned short) ; 
 int xgifb_reg_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xgifb_reg_or (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,int,unsigned short) ; 

__attribute__((used)) static void XGI_SetCRT1ModeRegs(struct xgi_hw_device_info *HwDeviceExtension,
				unsigned short ModeIdIndex,
				unsigned short RefreshRateTableIndex,
				struct vb_device_info *pVBInfo)
{
	unsigned short data, data2, data3, infoflag = 0, modeflag, resindex,
			xres;

	modeflag = XGI330_EModeIDTable[ModeIdIndex].Ext_ModeFlag;
	infoflag = XGI330_RefIndex[RefreshRateTableIndex].Ext_InfoFlag;

	if (xgifb_reg_get(pVBInfo->P3d4, 0x31) & 0x01)
		xgifb_reg_and_or(pVBInfo->P3c4, 0x1F, 0x3F, 0x00);

	data = infoflag;
	data2 = 0;
	data2 |= 0x02;
	data3 = pVBInfo->ModeType - ModeVGA;
	data3 <<= 2;
	data2 |= data3;
	data &= InterlaceMode;

	if (data)
		data2 |= 0x20;

	xgifb_reg_and_or(pVBInfo->P3c4, 0x06, ~0x3F, data2);
	resindex = XGI330_EModeIDTable[ModeIdIndex].Ext_RESINFO;
	xres = XGI330_ModeResInfo[resindex].HTotal; /* xres->ax */

	data = 0x0000;
	if (infoflag & InterlaceMode) {
		if (xres == 1024)
			data = 0x0035;
		else if (xres == 1280)
			data = 0x0048;
	}

	xgifb_reg_and_or(pVBInfo->P3d4, 0x19, 0xFF, data);
	xgifb_reg_and_or(pVBInfo->P3d4, 0x19, 0xFC, 0);

	if (modeflag & HalfDCLK)
		xgifb_reg_and_or(pVBInfo->P3c4, 0x01, 0xF7, 0x08);

	data2 = 0;

	if (modeflag & LineCompareOff)
		data2 |= 0x08;

	xgifb_reg_and_or(pVBInfo->P3c4, 0x0F, ~0x48, data2);
	data = 0x60;
	data = data ^ 0x60;
	data = data ^ 0xA0;
	xgifb_reg_and_or(pVBInfo->P3c4, 0x21, 0x1F, data);

	XGI_SetVCLKState(HwDeviceExtension, RefreshRateTableIndex, pVBInfo);

	data = xgifb_reg_get(pVBInfo->P3d4, 0x31);

	if (HwDeviceExtension->jChipType == XG27) {
		if (data & 0x40)
			data = 0x2c;
		else
			data = 0x6c;
		xgifb_reg_set(pVBInfo->P3d4, 0x52, data);
		xgifb_reg_or(pVBInfo->P3d4, 0x51, 0x10);
	} else if (HwDeviceExtension->jChipType >= XG20) {
		if (data & 0x40)
			data = 0x33;
		else
			data = 0x73;
		xgifb_reg_set(pVBInfo->P3d4, 0x52, data);
		xgifb_reg_set(pVBInfo->P3d4, 0x51, 0x02);
	} else {
		if (data & 0x40)
			data = 0x2c;
		else
			data = 0x6c;
		xgifb_reg_set(pVBInfo->P3d4, 0x52, data);
	}
}