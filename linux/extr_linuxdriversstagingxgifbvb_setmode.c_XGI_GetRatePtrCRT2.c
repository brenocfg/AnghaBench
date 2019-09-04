#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct xgi_hw_device_info {scalar_t__ jChipType; } ;
struct vb_device_info {unsigned short SelectCRT2Rate; int LCDInfo; int SetFlag; int VBInfo; int LCDResInfo; unsigned short ModeType; int /*<<< orphan*/  P3d4; } ;
struct TYPE_4__ {unsigned short REFindex; } ;
struct TYPE_3__ {unsigned short ModeID; int XRes; int YRes; unsigned short Ext_InfoFlag; } ;

/* Variables and functions */
 unsigned short InterlaceMode ; 
 int LCDNonExpanding ; 
 unsigned short ModeTypeMask ; 
 int ProgrammingCRT2 ; 
 int SetCRT2ToLCD ; 
 int SetCRT2ToRAMDAC ; 
 int SetInSlaveMode ; 
 scalar_t__ XG20 ; 
 TYPE_2__* XGI330_EModeIDTable ; 
 TYPE_1__* XGI330_RefIndex ; 
 unsigned short XGI_AjustCRT2Rate (unsigned short,unsigned short,unsigned short*,struct vb_device_info*) ; 
 int XGI_SetCRT2ToLCDA ; 
 unsigned short xgifb_reg_get (int /*<<< orphan*/ ,int) ; 

unsigned short XGI_GetRatePtrCRT2(struct xgi_hw_device_info *pXGIHWDE,
				  unsigned short ModeNo,
				  unsigned short ModeIdIndex,
				  struct vb_device_info *pVBInfo)
{
	static const u8 LCDARefreshIndex[] = {
		0x00, 0x00, 0x03, 0x01, 0x01, 0x01, 0x01, 0x00 };

	unsigned short RefreshRateTableIndex, i, index, temp;

	index = xgifb_reg_get(pVBInfo->P3d4, 0x33);
	index >>= pVBInfo->SelectCRT2Rate;
	index &= 0x0F;

	if (pVBInfo->LCDInfo & LCDNonExpanding)
		index = 0;

	if (index > 0)
		index--;

	if (pVBInfo->SetFlag & ProgrammingCRT2) {
		if (pVBInfo->VBInfo & (SetCRT2ToLCD | XGI_SetCRT2ToLCDA)) {
			temp = LCDARefreshIndex[pVBInfo->LCDResInfo & 0x07];

			if (index > temp)
				index = temp;
		}
	}

	RefreshRateTableIndex = XGI330_EModeIDTable[ModeIdIndex].REFindex;
	ModeNo = XGI330_RefIndex[RefreshRateTableIndex].ModeID;
	if (pXGIHWDE->jChipType >= XG20) { /* for XG20, XG21, XG27 */
		if ((XGI330_RefIndex[RefreshRateTableIndex].XRes == 800) &&
		    (XGI330_RefIndex[RefreshRateTableIndex].YRes == 600)) {
			index++;
		}
		/* do the similar adjustment like XGISearchCRT1Rate() */
		if ((XGI330_RefIndex[RefreshRateTableIndex].XRes == 1024) &&
		    (XGI330_RefIndex[RefreshRateTableIndex].YRes == 768)) {
			index++;
		}
		if ((XGI330_RefIndex[RefreshRateTableIndex].XRes == 1280) &&
		    (XGI330_RefIndex[RefreshRateTableIndex].YRes == 1024)) {
			index++;
		}
	}

	i = 0;
	do {
		if (XGI330_RefIndex[RefreshRateTableIndex + i].ModeID != ModeNo)
			break;
		temp = XGI330_RefIndex[RefreshRateTableIndex + i].Ext_InfoFlag;
		temp &= ModeTypeMask;
		if (temp < pVBInfo->ModeType)
			break;
		i++;
		index--;

	} while (index != 0xFFFF);
	if (!(pVBInfo->VBInfo & SetCRT2ToRAMDAC)) {
		if (pVBInfo->VBInfo & SetInSlaveMode) {
			temp = XGI330_RefIndex[RefreshRateTableIndex + i - 1].Ext_InfoFlag;
			if (temp & InterlaceMode)
				i++;
		}
	}
	i--;
	if ((pVBInfo->SetFlag & ProgrammingCRT2)) {
		temp = XGI_AjustCRT2Rate(ModeIdIndex, RefreshRateTableIndex,
					 &i, pVBInfo);
	}
	return RefreshRateTableIndex + i;
}