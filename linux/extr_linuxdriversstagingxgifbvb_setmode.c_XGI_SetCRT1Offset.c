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
struct vb_device_info {unsigned short ModeType; int /*<<< orphan*/  P3c4; int /*<<< orphan*/  P3d4; } ;
struct TYPE_4__ {unsigned short Ext_ModeInfo; } ;
struct TYPE_3__ {unsigned short Ext_InfoFlag; } ;

/* Variables and functions */
 unsigned short InterlaceMode ; 
 unsigned short ModeEGA ; 
 scalar_t__ XG20 ; 
 TYPE_2__* XGI330_EModeIDTable ; 
 TYPE_1__* XGI330_RefIndex ; 
 unsigned short* XGI330_ScreenOffset ; 
 unsigned short xgifb_reg_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,int,unsigned short) ; 

__attribute__((used)) static void XGI_SetCRT1Offset(unsigned short ModeNo,
			      unsigned short ModeIdIndex,
			      unsigned short RefreshRateTableIndex,
			      struct xgi_hw_device_info *HwDeviceExtension,
			      struct vb_device_info *pVBInfo)
{
	unsigned short temp, ah, al, temp2, i, DisplayUnit;

	/* GetOffset */
	temp = XGI330_EModeIDTable[ModeIdIndex].Ext_ModeInfo;
	temp >>= 8;
	temp = XGI330_ScreenOffset[temp];

	temp2 = XGI330_RefIndex[RefreshRateTableIndex].Ext_InfoFlag;
	temp2 &= InterlaceMode;

	if (temp2)
		temp <<= 1;

	temp2 = pVBInfo->ModeType - ModeEGA;

	switch (temp2) {
	case 0:
		temp2 = 1;
		break;
	case 1:
		temp2 = 2;
		break;
	case 2:
		temp2 = 4;
		break;
	case 3:
		temp2 = 4;
		break;
	case 4:
		temp2 = 6;
		break;
	case 5:
		temp2 = 8;
		break;
	default:
		break;
	}

	if ((ModeNo >= 0x26) && (ModeNo <= 0x28))
		temp = temp * temp2 + temp2 / 2;
	else
		temp *= temp2;

	/* SetOffset */
	DisplayUnit = temp;
	temp2 = temp;
	temp >>= 8; /* ah */
	temp &= 0x0F;
	i = xgifb_reg_get(pVBInfo->P3c4, 0x0E);
	i &= 0xF0;
	i |= temp;
	xgifb_reg_set(pVBInfo->P3c4, 0x0E, i);

	temp = (unsigned char)temp2;
	temp &= 0xFF; /* al */
	xgifb_reg_set(pVBInfo->P3d4, 0x13, temp);

	/* SetDisplayUnit */
	temp2 = XGI330_RefIndex[RefreshRateTableIndex].Ext_InfoFlag;
	temp2 &= InterlaceMode;
	if (temp2)
		DisplayUnit >>= 1;

	DisplayUnit <<= 5;
	ah = (DisplayUnit & 0xff00) >> 8;
	al = DisplayUnit & 0x00ff;
	if (al == 0)
		ah += 1;
	else
		ah += 2;

	if (HwDeviceExtension->jChipType >= XG20)
		if ((ModeNo == 0x4A) | (ModeNo == 0x49))
			ah -= 1;

	xgifb_reg_set(pVBInfo->P3c4, 0x10, ah);
}