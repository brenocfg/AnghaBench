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
struct xgi_hw_device_info {scalar_t__ jChipType; } ;
struct TYPE_2__ {unsigned char* data; } ;
struct vb_device_info {int /*<<< orphan*/  P3c4; int /*<<< orphan*/  P3d4; TYPE_1__ TimingH; } ;

/* Variables and functions */
 scalar_t__ XG20 ; 
 int /*<<< orphan*/  xgifb_reg_and_or (int /*<<< orphan*/ ,int,int,unsigned char) ; 
 void* xgifb_reg_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,int,unsigned char) ; 

__attribute__((used)) static void XGI_SetCRT1Timing_H(struct vb_device_info *pVBInfo,
				struct xgi_hw_device_info *HwDeviceExtension)
{
	unsigned char data, data1, pushax;
	unsigned short i, j;

	/* unlock cr0-7 */
	data = xgifb_reg_get(pVBInfo->P3d4, 0x11);
	data &= 0x7F;
	xgifb_reg_set(pVBInfo->P3d4, 0x11, data);

	data = pVBInfo->TimingH.data[0];
	xgifb_reg_set(pVBInfo->P3d4, 0, data);

	for (i = 0x01; i <= 0x04; i++) {
		data = pVBInfo->TimingH.data[i];
		xgifb_reg_set(pVBInfo->P3d4, (unsigned short)(i + 1), data);
	}

	for (i = 0x05; i <= 0x06; i++) {
		data = pVBInfo->TimingH.data[i];
		xgifb_reg_set(pVBInfo->P3c4, (unsigned short)(i + 6), data);
	}

	j = xgifb_reg_get(pVBInfo->P3c4, 0x0e);
	j &= 0x1F;
	data = pVBInfo->TimingH.data[7];
	data &= 0xE0;
	data |= j;
	xgifb_reg_set(pVBInfo->P3c4, 0x0e, data);

	if (HwDeviceExtension->jChipType >= XG20) {
		data = xgifb_reg_get(pVBInfo->P3d4, 0x04);
		data = data - 1;
		xgifb_reg_set(pVBInfo->P3d4, 0x04, data);
		data = xgifb_reg_get(pVBInfo->P3d4, 0x05);
		data1 = data;
		data1 &= 0xE0;
		data &= 0x1F;
		if (data == 0) {
			pushax = data;
			data = xgifb_reg_get(pVBInfo->P3c4, 0x0c);
			data &= 0xFB;
			xgifb_reg_set(pVBInfo->P3c4, 0x0c, data);
			data = pushax;
		}
		data = data - 1;
		data |= data1;
		xgifb_reg_set(pVBInfo->P3d4, 0x05, data);
		data = xgifb_reg_get(pVBInfo->P3c4, 0x0e);
		data >>= 5;
		data = data + 3;
		if (data > 7)
			data = data - 7;
		data <<= 5;
		xgifb_reg_and_or(pVBInfo->P3c4, 0x0e, ~0xE0, data);
	}
}