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
struct vb_device_info {TYPE_1__* LCDCapList; } ;
struct TYPE_2__ {unsigned short LCD_HSyncWidth; unsigned short LCD_VSyncWidth; } ;

/* Variables and functions */
 unsigned short XGI_GetLCDCapPtr (struct vb_device_info*) ; 

__attribute__((used)) static void XGI_GetLCDSync(unsigned short *HSyncWidth,
			   unsigned short *VSyncWidth,
			   struct vb_device_info *pVBInfo)
{
	unsigned short Index;

	Index = XGI_GetLCDCapPtr(pVBInfo);
	*HSyncWidth = pVBInfo->LCDCapList[Index].LCD_HSyncWidth;
	*VSyncWidth = pVBInfo->LCDCapList[Index].LCD_VSyncWidth;
}