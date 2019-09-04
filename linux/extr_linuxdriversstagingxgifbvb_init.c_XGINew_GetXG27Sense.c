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
 int /*<<< orphan*/  LCDSense ; 
 int /*<<< orphan*/  xgifb_reg_and_or (int /*<<< orphan*/ ,int,int,int) ; 
 int xgifb_reg_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xgifb_reg_or (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void XGINew_GetXG27Sense(struct vb_device_info *pVBInfo)
{
	unsigned char Temp, bCR4A;

	bCR4A = xgifb_reg_get(pVBInfo->P3d4, 0x4A);
	/* Enable GPIOA/B/C read */
	xgifb_reg_and_or(pVBInfo->P3d4, 0x4A, ~0x07, 0x07);
	Temp = xgifb_reg_get(pVBInfo->P3d4, 0x48) & 0x07;
	xgifb_reg_set(pVBInfo->P3d4, 0x4A, bCR4A);

	if (Temp <= 0x02) {
		/* LVDS setting */
		xgifb_reg_and_or(pVBInfo->P3d4, 0x38, ~0xE0, 0xC0);
		xgifb_reg_set(pVBInfo->P3d4, 0x30, 0x21);
	} else {
		/* TMDS/DVO setting */
		xgifb_reg_and_or(pVBInfo->P3d4, 0x38, ~0xE0, 0xA0);
	}
	xgifb_reg_or(pVBInfo->P3d4, 0x32, LCDSense);
}