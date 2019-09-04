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
struct vb_device_info {int /*<<< orphan*/  P3d4; } ;

/* Variables and functions */
 unsigned short AVIDEOSense ; 
 int ActiveAVideo ; 
 unsigned short ActiveCRT1 ; 
 unsigned short ActiveCRT2 ; 
 int ActiveHiTV ; 
 unsigned short ActiveLCD ; 
 int ActiveSCART ; 
 int ActiveSVideo ; 
 unsigned short ActiveTV ; 
 int ActiveYPbPr ; 
 unsigned short DisplayDeviceFromCMOS ; 
 unsigned short HiTVSense ; 
 unsigned short LCDSense ; 
 unsigned short Monitor1Sense ; 
 unsigned short Monitor2Sense ; 
 unsigned short SCARTSense ; 
 unsigned short SVIDEOSense ; 
 unsigned short TVSense ; 
 unsigned short YPbPrSense ; 
 int xgifb_reg_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,int,unsigned short) ; 

__attribute__((used)) static void XGINew_ChkSenseStatus(struct vb_device_info *pVBInfo)
{
	unsigned short tempbx = 0, temp, tempcx, CR3CData;

	temp = xgifb_reg_get(pVBInfo->P3d4, 0x32);

	if (temp & Monitor1Sense)
		tempbx |= ActiveCRT1;
	if (temp & LCDSense)
		tempbx |= ActiveLCD;
	if (temp & Monitor2Sense)
		tempbx |= ActiveCRT2;
	if (temp & TVSense) {
		tempbx |= ActiveTV;
		if (temp & AVIDEOSense)
			tempbx |= (ActiveAVideo << 8);
		if (temp & SVIDEOSense)
			tempbx |= (ActiveSVideo << 8);
		if (temp & SCARTSense)
			tempbx |= (ActiveSCART << 8);
		if (temp & HiTVSense)
			tempbx |= (ActiveHiTV << 8);
		if (temp & YPbPrSense)
			tempbx |= (ActiveYPbPr << 8);
	}

	tempcx = xgifb_reg_get(pVBInfo->P3d4, 0x3d);
	tempcx |= (xgifb_reg_get(pVBInfo->P3d4, 0x3e) << 8);

	if (tempbx & tempcx) {
		CR3CData = xgifb_reg_get(pVBInfo->P3d4, 0x3c);
		if (!(CR3CData & DisplayDeviceFromCMOS))
			tempcx = 0x1FF0;
	} else {
		tempcx = 0x1FF0;
	}

	tempbx &= tempcx;
	xgifb_reg_set(pVBInfo->P3d4, 0x3d, (tempbx & 0x00FF));
	xgifb_reg_set(pVBInfo->P3d4, 0x3e, ((tempbx & 0xFF00) >> 8));
}