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
struct vb_device_info {int /*<<< orphan*/  P3d4; } ;
struct TYPE_2__ {unsigned char* CRTC; } ;

/* Variables and functions */
 TYPE_1__ XGI330_StandTable ; 
 unsigned char xgifb_reg_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,unsigned short,unsigned char) ; 

__attribute__((used)) static void XGI_SetCRTCRegs(struct vb_device_info *pVBInfo)
{
	unsigned char CRTCdata;
	unsigned short i;

	CRTCdata = xgifb_reg_get(pVBInfo->P3d4, 0x11);
	CRTCdata &= 0x7f;
	xgifb_reg_set(pVBInfo->P3d4, 0x11, CRTCdata); /* Unlock CRTC */

	for (i = 0; i <= 0x18; i++) {
		/* Get CRTC from file */
		CRTCdata = XGI330_StandTable.CRTC[i];
		xgifb_reg_set(pVBInfo->P3d4, i, CRTCdata); /* Set CRTC(3d4) */
	}
}