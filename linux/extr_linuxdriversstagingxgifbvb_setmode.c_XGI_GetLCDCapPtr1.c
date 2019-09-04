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
struct vb_device_info {unsigned short LCDResInfo; unsigned short LCDTypeInfo; TYPE_1__* LCDCapList; } ;
struct TYPE_2__ {unsigned short LCD_ID; } ;

/* Variables and functions */
 unsigned short Panel_1024x768 ; 

__attribute__((used)) static unsigned short XGI_GetLCDCapPtr1(struct vb_device_info *pVBInfo)
{
	unsigned short tempah, tempal, tempbl, i;

	tempal = pVBInfo->LCDResInfo;
	tempah = pVBInfo->LCDTypeInfo;

	i = 0;
	tempbl = pVBInfo->LCDCapList[i].LCD_ID;

	while (tempbl != 0xFF) {
		if ((tempbl & 0x80) && (tempbl != 0x80)) {
			tempal = tempah;
			tempbl &= ~0x80;
		}

		if (tempal == tempbl)
			break;

		i++;
		tempbl = pVBInfo->LCDCapList[i].LCD_ID;
	}

	if (tempbl == 0xFF) {
		pVBInfo->LCDResInfo = Panel_1024x768;
		pVBInfo->LCDTypeInfo = 0;
		i = 0;
	}

	return i;
}