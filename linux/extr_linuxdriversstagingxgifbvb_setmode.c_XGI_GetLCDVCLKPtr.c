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
struct vb_device_info {int VBInfo; TYPE_1__* LCDCapList; } ;
struct TYPE_2__ {unsigned char LCUCHAR_VCLKData1; unsigned char LCUCHAR_VCLKData2; unsigned char LCDA_VCLKData1; unsigned char LCDA_VCLKData2; } ;

/* Variables and functions */
 int SetCRT2ToLCD ; 
 unsigned short XGI_GetLCDCapPtr1 (struct vb_device_info*) ; 
 int XGI_SetCRT2ToLCDA ; 

__attribute__((used)) static void XGI_GetLCDVCLKPtr(unsigned char *di_0, unsigned char *di_1,
			      struct vb_device_info *pVBInfo)
{
	unsigned short index;

	if (pVBInfo->VBInfo & (SetCRT2ToLCD | XGI_SetCRT2ToLCDA)) {
		index = XGI_GetLCDCapPtr1(pVBInfo);

		if (pVBInfo->VBInfo & SetCRT2ToLCD) { /* LCDB */
			*di_0 = pVBInfo->LCDCapList[index].LCUCHAR_VCLKData1;
			*di_1 = pVBInfo->LCDCapList[index].LCUCHAR_VCLKData2;
		} else { /* LCDA */
			*di_0 = pVBInfo->LCDCapList[index].LCDA_VCLKData1;
			*di_1 = pVBInfo->LCDCapList[index].LCDA_VCLKData2;
		}
	}
}