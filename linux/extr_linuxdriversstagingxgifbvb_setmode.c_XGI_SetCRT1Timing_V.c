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
struct TYPE_3__ {unsigned char* data; } ;
struct vb_device_info {int /*<<< orphan*/  P3d4; TYPE_1__ TimingV; int /*<<< orphan*/  P3c4; } ;
struct TYPE_4__ {unsigned short Ext_ModeFlag; } ;

/* Variables and functions */
 unsigned short DoubleScanMode ; 
 TYPE_2__* XGI330_EModeIDTable ; 
 unsigned short xgifb_reg_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,int,unsigned char) ; 

__attribute__((used)) static void XGI_SetCRT1Timing_V(unsigned short ModeIdIndex,
				struct vb_device_info *pVBInfo)
{
	unsigned char data;
	unsigned short i, j;

	for (i = 0x00; i <= 0x01; i++) {
		data = pVBInfo->TimingV.data[i];
		xgifb_reg_set(pVBInfo->P3d4, (unsigned short)(i + 6), data);
	}

	for (i = 0x02; i <= 0x03; i++) {
		data = pVBInfo->TimingV.data[i];
		xgifb_reg_set(pVBInfo->P3d4, (unsigned short)(i + 0x0e), data);
	}

	for (i = 0x04; i <= 0x05; i++) {
		data = pVBInfo->TimingV.data[i];
		xgifb_reg_set(pVBInfo->P3d4, (unsigned short)(i + 0x11), data);
	}

	j = xgifb_reg_get(pVBInfo->P3c4, 0x0a);
	j &= 0xC0;
	data = pVBInfo->TimingV.data[6];
	data &= 0x3F;
	data |= j;
	xgifb_reg_set(pVBInfo->P3c4, 0x0a, data);

	data = pVBInfo->TimingV.data[6];
	data &= 0x80;
	data >>= 2;

	i = XGI330_EModeIDTable[ModeIdIndex].Ext_ModeFlag;
	i &= DoubleScanMode;
	if (i)
		data |= 0x80;

	j = xgifb_reg_get(pVBInfo->P3d4, 0x09);
	j &= 0x5F;
	data |= j;
	xgifb_reg_set(pVBInfo->P3d4, 0x09, data);
}