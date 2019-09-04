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
struct vb_device_info {int VBType; int XGINew_CR97; int /*<<< orphan*/  P3c4; int /*<<< orphan*/  SR18; int /*<<< orphan*/  CR40; int /*<<< orphan*/  MCLKData; int /*<<< orphan*/  LCDCapList; scalar_t__ TVInfo; scalar_t__ VBInfo; scalar_t__ LCDInfo; scalar_t__ LCDTypeInfo; scalar_t__ LCDResInfo; } ;

/* Variables and functions */
 int VB_SIS301LV ; 
 int VB_SIS302LV ; 
 unsigned char XG20 ; 
 unsigned char XG27 ; 
 int /*<<< orphan*/  XG27_SR18 ; 
 int /*<<< orphan*/  XGI27New_MCLKData ; 
 int /*<<< orphan*/  XGI27_cr41 ; 
 int /*<<< orphan*/  XGI340New_MCLKData ; 
 int /*<<< orphan*/  XGI340_SR18 ; 
 int /*<<< orphan*/  XGI340_cr41 ; 
 int /*<<< orphan*/  XGI_GetVBType (struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_LCDCapList ; 
 int /*<<< orphan*/  XGI_LCDDLCapList ; 
 unsigned char xgifb_reg_get (int /*<<< orphan*/ ,int) ; 

void InitTo330Pointer(unsigned char ChipType, struct vb_device_info *pVBInfo)
{
	pVBInfo->MCLKData = XGI340New_MCLKData;

	pVBInfo->LCDResInfo = 0;
	pVBInfo->LCDTypeInfo = 0;
	pVBInfo->LCDInfo = 0;
	pVBInfo->VBInfo = 0;
	pVBInfo->TVInfo = 0;

	pVBInfo->SR18 = XGI340_SR18;
	pVBInfo->CR40 = XGI340_cr41;

	if (ChipType < XG20)
		XGI_GetVBType(pVBInfo);

	/* 310 customization related */
	if ((pVBInfo->VBType & VB_SIS301LV) || (pVBInfo->VBType & VB_SIS302LV))
		pVBInfo->LCDCapList = XGI_LCDDLCapList;
	else
		pVBInfo->LCDCapList = XGI_LCDCapList;

	if (ChipType >= XG20)
		pVBInfo->XGINew_CR97 = 0x10;

	if (ChipType == XG27) {
		unsigned char temp;

		pVBInfo->MCLKData = XGI27New_MCLKData;
		pVBInfo->CR40 = XGI27_cr41;
		pVBInfo->XGINew_CR97 = 0xc1;
		pVBInfo->SR18 = XG27_SR18;

		/* Z11m DDR */
		temp = xgifb_reg_get(pVBInfo->P3c4, 0x3B);
		/* SR3B[7][3]MAA15 MAA11 (Power on Trapping) */
		if (((temp & 0x88) == 0x80) || ((temp & 0x88) == 0x08))
			pVBInfo->XGINew_CR97 = 0x80;
	}
}