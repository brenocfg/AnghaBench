#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct xgi_hw_device_info {scalar_t__ jChipType; } ;
struct vb_device_info {scalar_t__ IF_DEF_LVDS; int VBType; int VBInfo; int /*<<< orphan*/  P3c4; } ;
struct TYPE_8__ {int Ext_ModeFlag; } ;
struct TYPE_7__ {unsigned char Ext_CRTVCLK; } ;
struct TYPE_6__ {unsigned char Part4_A; unsigned char Part4_B; } ;
struct TYPE_5__ {unsigned char SR2B; unsigned char SR2C; } ;

/* Variables and functions */
 int HalfDCLK ; 
 int VB_SIS301B ; 
 int VB_SIS301LV ; 
 int VB_SIS302B ; 
 int VB_SIS302LV ; 
 int VB_XGI301C ; 
 scalar_t__ XG20 ; 
 TYPE_4__* XGI330_EModeIDTable ; 
 TYPE_3__* XGI330_RefIndex ; 
 unsigned short XGI_GetVCLK2Ptr (unsigned short,unsigned short,struct vb_device_info*) ; 
 int XGI_SetCRT2ToLCDA ; 
 TYPE_2__* XGI_VBVCLKData ; 
 TYPE_1__* XGI_VCLKData ; 
 int xgifb_reg_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,int,unsigned char) ; 

__attribute__((used)) static void XGI_SetCRT1VCLK(unsigned short ModeIdIndex,
			    struct xgi_hw_device_info *HwDeviceExtension,
			    unsigned short RefreshRateTableIndex,
			    struct vb_device_info *pVBInfo)
{
	unsigned char index, data;
	unsigned short vclkindex;

	if ((pVBInfo->IF_DEF_LVDS == 0) &&
	    (pVBInfo->VBType & (VB_SIS301B | VB_SIS302B | VB_SIS301LV |
				VB_SIS302LV | VB_XGI301C)) &&
	    (pVBInfo->VBInfo & XGI_SetCRT2ToLCDA)) {
		vclkindex = XGI_GetVCLK2Ptr(ModeIdIndex, RefreshRateTableIndex,
					    pVBInfo);
		data = xgifb_reg_get(pVBInfo->P3c4, 0x31) & 0xCF;
		xgifb_reg_set(pVBInfo->P3c4, 0x31, data);
		data = XGI_VBVCLKData[vclkindex].Part4_A;
		xgifb_reg_set(pVBInfo->P3c4, 0x2B, data);
		data = XGI_VBVCLKData[vclkindex].Part4_B;
		xgifb_reg_set(pVBInfo->P3c4, 0x2C, data);
		xgifb_reg_set(pVBInfo->P3c4, 0x2D, 0x01);
	} else {
		index = XGI330_RefIndex[RefreshRateTableIndex].Ext_CRTVCLK;
		data = xgifb_reg_get(pVBInfo->P3c4, 0x31) & 0xCF;
		xgifb_reg_set(pVBInfo->P3c4, 0x31, data);
		xgifb_reg_set(pVBInfo->P3c4, 0x2B, XGI_VCLKData[index].SR2B);
		xgifb_reg_set(pVBInfo->P3c4, 0x2C, XGI_VCLKData[index].SR2C);
		xgifb_reg_set(pVBInfo->P3c4, 0x2D, 0x01);
	}

	if (HwDeviceExtension->jChipType >= XG20) {
		if (XGI330_EModeIDTable[ModeIdIndex].Ext_ModeFlag &
		    HalfDCLK) {
			data = xgifb_reg_get(pVBInfo->P3c4, 0x2B);
			xgifb_reg_set(pVBInfo->P3c4, 0x2B, data);
			data = xgifb_reg_get(pVBInfo->P3c4, 0x2C);
			index = data;
			index &= 0xE0;
			data &= 0x1F;
			data <<= 1;
			data += 1;
			data |= index;
			xgifb_reg_set(pVBInfo->P3c4, 0x2C, data);
		}
	}
}