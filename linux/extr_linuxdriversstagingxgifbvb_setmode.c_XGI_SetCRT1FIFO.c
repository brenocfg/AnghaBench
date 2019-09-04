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
struct vb_device_info {int /*<<< orphan*/  P3c4; } ;

/* Variables and functions */
 scalar_t__ XG21 ; 
 int /*<<< orphan*/  XGI_SetXG21FPBits (struct vb_device_info*) ; 
 unsigned short xgifb_reg_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,int,unsigned short) ; 

__attribute__((used)) static void XGI_SetCRT1FIFO(struct xgi_hw_device_info *HwDeviceExtension,
			    struct vb_device_info *pVBInfo)
{
	unsigned short data;

	data = xgifb_reg_get(pVBInfo->P3c4, 0x3D);
	data &= 0xfe;
	xgifb_reg_set(pVBInfo->P3c4, 0x3D, data); /* disable auto-threshold */

	xgifb_reg_set(pVBInfo->P3c4, 0x08, 0x34);
	data = xgifb_reg_get(pVBInfo->P3c4, 0x09);
	data &= 0xC0;
	xgifb_reg_set(pVBInfo->P3c4, 0x09, data | 0x30);
	data = xgifb_reg_get(pVBInfo->P3c4, 0x3D);
	data |= 0x01;
	xgifb_reg_set(pVBInfo->P3c4, 0x3D, data);

	if (HwDeviceExtension->jChipType == XG21)
		XGI_SetXG21FPBits(pVBInfo); /* Fix SR9[7:6] can't read back */
}