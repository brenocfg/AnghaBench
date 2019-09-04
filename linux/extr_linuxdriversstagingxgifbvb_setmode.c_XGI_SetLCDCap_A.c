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
struct vb_device_info {int /*<<< orphan*/  Part1Port; int /*<<< orphan*/  P3d4; } ;

/* Variables and functions */
 unsigned short LCDRGB18Bit ; 
 int /*<<< orphan*/  xgifb_reg_and_or (int /*<<< orphan*/ ,int,int,int) ; 
 unsigned short xgifb_reg_get (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void XGI_SetLCDCap_A(unsigned short tempcx,
			    struct vb_device_info *pVBInfo)
{
	unsigned short temp;

	temp = xgifb_reg_get(pVBInfo->P3d4, 0x37);

	if (temp & LCDRGB18Bit) {
		xgifb_reg_and_or(pVBInfo->Part1Port, 0x19, 0x0F,
				 /* Enable Dither */
				 (unsigned short)(0x20 | (tempcx & 0x00C0)));
		xgifb_reg_and_or(pVBInfo->Part1Port, 0x1A, 0x7F, 0x80);
	} else {
		xgifb_reg_and_or(pVBInfo->Part1Port, 0x19, 0x0F,
				 (unsigned short)(0x30 | (tempcx & 0x00C0)));
		xgifb_reg_and_or(pVBInfo->Part1Port, 0x1A, 0x7F, 0x00);
	}
}