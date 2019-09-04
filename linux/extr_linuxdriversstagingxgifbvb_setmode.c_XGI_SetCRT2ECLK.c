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
struct vb_device_info {int VBInfo; int /*<<< orphan*/  P3c4; int /*<<< orphan*/  P3d4; } ;

/* Variables and functions */
 int SetInSlaveMode ; 
 int /*<<< orphan*/  XGI_GetLCDVCLKPtr (unsigned char*,unsigned char*,struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_GetVCLKLen (unsigned char,unsigned char*,unsigned char*,struct vb_device_info*) ; 
 unsigned char XGI_GetVCLKPtr (unsigned short,unsigned short,struct vb_device_info*) ; 
 int XGI_SetCRT2ToLCDA ; 
 int /*<<< orphan*/  xgifb_reg_and_or (int /*<<< orphan*/ ,int,int,unsigned short) ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,int,unsigned char) ; 

__attribute__((used)) static void XGI_SetCRT2ECLK(unsigned short ModeIdIndex,
			    unsigned short RefreshRateTableIndex,
			    struct vb_device_info *pVBInfo)
{
	unsigned char di_0, di_1, tempal;
	int i;

	tempal = XGI_GetVCLKPtr(RefreshRateTableIndex, ModeIdIndex, pVBInfo);
	XGI_GetVCLKLen(tempal, &di_0, &di_1, pVBInfo);
	XGI_GetLCDVCLKPtr(&di_0, &di_1, pVBInfo);

	for (i = 0; i < 4; i++) {
		xgifb_reg_and_or(pVBInfo->P3d4, 0x31, ~0x30,
				 (unsigned short)(0x10 * i));
		if (!(pVBInfo->VBInfo & XGI_SetCRT2ToLCDA) &&
		    !(pVBInfo->VBInfo & SetInSlaveMode)) {
			xgifb_reg_set(pVBInfo->P3c4, 0x2e, di_0);
			xgifb_reg_set(pVBInfo->P3c4, 0x2f, di_1);
		} else {
			xgifb_reg_set(pVBInfo->P3c4, 0x2b, di_0);
			xgifb_reg_set(pVBInfo->P3c4, 0x2c, di_1);
		}
	}
}