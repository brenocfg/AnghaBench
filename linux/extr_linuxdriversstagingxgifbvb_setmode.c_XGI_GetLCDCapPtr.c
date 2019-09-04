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
struct vb_device_info {TYPE_1__* LCDCapList; int /*<<< orphan*/  P3d4; } ;
struct TYPE_2__ {unsigned char LCD_ID; } ;

/* Variables and functions */
 unsigned char xgifb_reg_get (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static unsigned short XGI_GetLCDCapPtr(struct vb_device_info *pVBInfo)
{
	unsigned char tempal, tempah, tempbl, i;

	tempah = xgifb_reg_get(pVBInfo->P3d4, 0x36);
	tempal = tempah & 0x0F;
	tempah = tempah & 0xF0;
	i = 0;
	tempbl = pVBInfo->LCDCapList[i].LCD_ID;

	while (tempbl != 0xFF) {
		if (tempbl & 0x80) { /* OEMUtil */
			tempal = tempah;
			tempbl = tempbl & ~(0x80);
		}

		if (tempal == tempbl)
			break;

		i++;

		tempbl = pVBInfo->LCDCapList[i].LCD_ID;
	}

	return i;
}