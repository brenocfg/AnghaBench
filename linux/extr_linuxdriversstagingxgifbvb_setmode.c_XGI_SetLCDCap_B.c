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
struct vb_device_info {int /*<<< orphan*/  Part2Port; } ;

/* Variables and functions */
 unsigned short EnableLCD24bpp ; 
 int /*<<< orphan*/  xgifb_reg_and_or (int /*<<< orphan*/ ,int,int,unsigned short) ; 

__attribute__((used)) static void XGI_SetLCDCap_B(unsigned short tempcx,
			    struct vb_device_info *pVBInfo)
{
	if (tempcx & EnableLCD24bpp) { /* 24bits */
		xgifb_reg_and_or(pVBInfo->Part2Port, 0x1A, 0xE0,
				 (unsigned short)(((tempcx & 0x00ff) >> 6) | 0x0c));
	} else {
		xgifb_reg_and_or(pVBInfo->Part2Port, 0x1A, 0xE0,
				 (unsigned short)(((tempcx & 0x00ff) >> 6) | 0x18));
				  /* Enable Dither */
	}
}