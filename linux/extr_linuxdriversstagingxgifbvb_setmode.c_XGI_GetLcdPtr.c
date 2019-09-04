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
struct vb_device_info {unsigned short LCDResInfo; unsigned short LCDTypeInfo; int LCDInfo; } ;
struct XGI330_LCDDataTablStruct {int PANELID; unsigned short MASK; unsigned short CAP; void const* DATAPTR; } ;
struct TYPE_2__ {unsigned short Ext_ModeFlag; } ;

/* Variables and functions */
 int EnableScalingLCD ; 
 unsigned short HalfDCLK ; 
 unsigned short PanelResInfo ; 
 unsigned short SetLCDLowResolution ; 
 TYPE_1__* XGI330_EModeIDTable ; 

__attribute__((used)) static void const *XGI_GetLcdPtr(struct XGI330_LCDDataTablStruct const *table,
				 unsigned short ModeIdIndex,
				 struct vb_device_info *pVBInfo)
{
	unsigned short i, tempdx, tempbx, modeflag;

	tempbx = 0;

	modeflag = XGI330_EModeIDTable[ModeIdIndex].Ext_ModeFlag;

	i = 0;

	while (table[i].PANELID != 0xff) {
		tempdx = pVBInfo->LCDResInfo;
		if (tempbx & 0x0080) { /* OEMUtil */
			tempbx &= ~0x0080;
			tempdx = pVBInfo->LCDTypeInfo;
		}

		if (pVBInfo->LCDInfo & EnableScalingLCD)
			tempdx &= ~PanelResInfo;

		if (table[i].PANELID == tempdx) {
			tempbx = table[i].MASK;
			tempdx = pVBInfo->LCDInfo;

			if (modeflag & HalfDCLK)
				tempdx |= SetLCDLowResolution;

			tempbx &= tempdx;
			if (tempbx == table[i].CAP)
				break;
		}
		i++;
	}

	return table[i].DATAPTR;
}