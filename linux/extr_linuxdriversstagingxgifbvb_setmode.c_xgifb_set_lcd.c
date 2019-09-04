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
struct vb_device_info {int /*<<< orphan*/  P3c4; int /*<<< orphan*/  P3d4; } ;
struct TYPE_2__ {unsigned short Ext_InfoFlag; } ;

/* Variables and functions */
 int XG27 ; 
 TYPE_1__* XGI330_RefIndex ; 
 int /*<<< orphan*/  XGI_SetXG27FPBits (struct vb_device_info*) ; 
 int /*<<< orphan*/  xgifb_reg_and (int /*<<< orphan*/ ,int,int) ; 
 unsigned short xgifb_reg_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xgifb_reg_or (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void xgifb_set_lcd(int chip_id,
			  struct vb_device_info *pVBInfo,
			  unsigned short RefreshRateTableIndex)
{
	unsigned short temp;

	xgifb_reg_set(pVBInfo->P3d4, 0x2E, 0x00);
	xgifb_reg_set(pVBInfo->P3d4, 0x2F, 0x00);
	xgifb_reg_set(pVBInfo->P3d4, 0x46, 0x00);
	xgifb_reg_set(pVBInfo->P3d4, 0x47, 0x00);

	if (chip_id == XG27) {
		temp = xgifb_reg_get(pVBInfo->P3d4, 0x37);
		if ((temp & 0x03) == 0) { /* dual 12 */
			xgifb_reg_set(pVBInfo->P3d4, 0x46, 0x13);
			xgifb_reg_set(pVBInfo->P3d4, 0x47, 0x13);
		}
	}

	if (chip_id == XG27) {
		XGI_SetXG27FPBits(pVBInfo);
	} else {
		temp = xgifb_reg_get(pVBInfo->P3d4, 0x37);
		if (temp & 0x01) {
			/* 18 bits FP */
			xgifb_reg_or(pVBInfo->P3c4, 0x06, 0x40);
			xgifb_reg_or(pVBInfo->P3c4, 0x09, 0x40);
		}
	}

	xgifb_reg_or(pVBInfo->P3c4, 0x1E, 0x01); /* Negative blank polarity */

	xgifb_reg_and(pVBInfo->P3c4, 0x30, ~0x20); /* Hsync polarity */
	xgifb_reg_and(pVBInfo->P3c4, 0x35, ~0x80); /* Vsync polarity */

	temp = XGI330_RefIndex[RefreshRateTableIndex].Ext_InfoFlag;
	if (temp & 0x4000) {
		/* Hsync polarity */
		xgifb_reg_or(pVBInfo->P3c4, 0x30, 0x20);
	}
	if (temp & 0x8000) {
		/* Vsync polarity */
		xgifb_reg_or(pVBInfo->P3c4, 0x35, 0x80);
	}
}