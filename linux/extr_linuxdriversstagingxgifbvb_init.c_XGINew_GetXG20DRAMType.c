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
struct xgi_hw_device_info {scalar_t__ jChipType; } ;
struct vb_device_info {int /*<<< orphan*/  P3d4; int /*<<< orphan*/  P3c4; } ;

/* Variables and functions */
 scalar_t__ XG20 ; 
 scalar_t__ XG21 ; 
 scalar_t__ XG27 ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  xgifb_reg_and (int /*<<< orphan*/ ,int,int) ; 
 int xgifb_reg_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xgifb_reg_or (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static unsigned char
XGINew_GetXG20DRAMType(struct xgi_hw_device_info *HwDeviceExtension,
		       struct vb_device_info *pVBInfo)
{
	unsigned char data, temp;

	if (HwDeviceExtension->jChipType < XG20) {
		data = xgifb_reg_get(pVBInfo->P3c4, 0x39) & 0x02;
		if (data == 0)
			data = (xgifb_reg_get(pVBInfo->P3c4, 0x3A) &
				   0x02) >> 1;
		return data;
	} else if (HwDeviceExtension->jChipType == XG27) {
		temp = xgifb_reg_get(pVBInfo->P3c4, 0x3B);
		/* SR3B[7][3]MAA15 MAA11 (Power on Trapping) */
		if (((temp & 0x88) == 0x80) || ((temp & 0x88) == 0x08))
			data = 0; /* DDR */
		else
			data = 1; /* DDRII */
		return data;
	} else if (HwDeviceExtension->jChipType == XG21) {
		/* Independent GPIO control */
		xgifb_reg_and(pVBInfo->P3d4, 0xB4, ~0x02);
		usleep_range(800, 1800);
		xgifb_reg_or(pVBInfo->P3d4, 0x4A, 0x80); /* Enable GPIOH read */
		/* GPIOF 0:DVI 1:DVO */
		data = xgifb_reg_get(pVBInfo->P3d4, 0x48);
		/*
		 * HOTPLUG_SUPPORT
		 * for current XG20 & XG21, GPIOH is floating, driver will
		 * fix DDR temporarily
		 */
		/* DVI read GPIOH */
		data &= 0x01; /* 1=DDRII, 0=DDR */
		/* ~HOTPLUG_SUPPORT */
		xgifb_reg_or(pVBInfo->P3d4, 0xB4, 0x02);
		return data;
	}
	data = xgifb_reg_get(pVBInfo->P3d4, 0x97) & 0x01;

	if (data == 1)
		data++;

	return data;
}