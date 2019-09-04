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
struct vb_device_info {int VBType; int VBInfo; int /*<<< orphan*/  Part4Port; } ;

/* Variables and functions */
 int SetCRT2ToRAMDAC ; 
 int VB_SIS301 ; 
 int /*<<< orphan*/  XGI_GetLCDVCLKPtr (unsigned char*,unsigned char*,struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_GetVCLKLen (unsigned char,unsigned char*,unsigned char*,struct vb_device_info*) ; 
 unsigned char XGI_GetVCLKPtr (unsigned short,unsigned short,struct vb_device_info*) ; 
 int /*<<< orphan*/  xgifb_reg_or (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void XGI_SetCRT2VCLK(unsigned short ModeIdIndex,
			    unsigned short RefreshRateTableIndex,
			    struct vb_device_info *pVBInfo)
{
	unsigned char di_0, di_1, tempal;

	tempal = XGI_GetVCLKPtr(RefreshRateTableIndex, ModeIdIndex, pVBInfo);
	XGI_GetVCLKLen(tempal, &di_0, &di_1, pVBInfo);
	XGI_GetLCDVCLKPtr(&di_0, &di_1, pVBInfo);

	if (pVBInfo->VBType & VB_SIS301) { /* shampoo 0129 */
		/* 301 */
		xgifb_reg_set(pVBInfo->Part4Port, 0x0A, 0x10);
		xgifb_reg_set(pVBInfo->Part4Port, 0x0B, di_1);
		xgifb_reg_set(pVBInfo->Part4Port, 0x0A, di_0);
	} else { /* 301b/302b/301lv/302lv */
		xgifb_reg_set(pVBInfo->Part4Port, 0x0A, di_0);
		xgifb_reg_set(pVBInfo->Part4Port, 0x0B, di_1);
	}

	xgifb_reg_set(pVBInfo->Part4Port, 0x00, 0x12);

	if (pVBInfo->VBInfo & SetCRT2ToRAMDAC)
		xgifb_reg_or(pVBInfo->Part4Port, 0x12, 0x28);
	else
		xgifb_reg_or(pVBInfo->Part4Port, 0x12, 0x08);
}