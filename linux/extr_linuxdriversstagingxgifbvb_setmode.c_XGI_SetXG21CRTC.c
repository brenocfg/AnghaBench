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
struct vb_device_info {int /*<<< orphan*/  P3c4; } ;
struct TYPE_4__ {unsigned char Ext_CRT1CRTC; } ;
struct TYPE_3__ {unsigned char* CR; } ;

/* Variables and functions */
 TYPE_2__* XGI330_RefIndex ; 
 TYPE_1__* XGI_CRT1Table ; 
 int /*<<< orphan*/  xgifb_reg_and_or (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  xgifb_reg_or (int /*<<< orphan*/ ,int,unsigned char) ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,int,unsigned char) ; 

__attribute__((used)) static void XGI_SetXG21CRTC(unsigned short RefreshRateTableIndex,
			    struct vb_device_info *pVBInfo)
{
	unsigned char index, Tempax, Tempbx, Tempcx, Tempdx;
	unsigned short Temp1, Temp2, Temp3;

	index = XGI330_RefIndex[RefreshRateTableIndex].Ext_CRT1CRTC;
	/* Tempax: CR4 HRS */
	Tempax = XGI_CRT1Table[index].CR[3];
	Tempcx = Tempax; /* Tempcx: HRS */
	/* SR2E[7:0]->HRS */
	xgifb_reg_set(pVBInfo->P3c4, 0x2E, Tempax);

	Tempdx = XGI_CRT1Table[index].CR[5]; /* SRB */
	Tempdx &= 0xC0; /* Tempdx[7:6]: SRB[7:6] */
	Temp1 = Tempdx; /* Temp1[7:6]: HRS[9:8] */
	Temp1 <<= 2; /* Temp1[9:8]: HRS[9:8] */
	Temp1 |= Tempax; /* Temp1[9:0]: HRS[9:0] */

	Tempax = XGI_CRT1Table[index].CR[4]; /* CR5 HRE */
	Tempax &= 0x1F; /* Tempax[4:0]: HRE[4:0] */

	Tempbx = XGI_CRT1Table[index].CR[6]; /* SRC */
	Tempbx &= 0x04; /* Tempbx[2]: HRE[5] */
	Tempbx <<= 3; /* Tempbx[5]: HRE[5] */
	Tempax |= Tempbx; /* Tempax[5:0]: HRE[5:0] */

	Temp2 = Temp1 & 0x3C0; /* Temp2[9:6]: HRS[9:6] */
	Temp2 |= Tempax; /* Temp2[9:0]: HRE[9:0] */

	Tempcx &= 0x3F; /* Tempcx[5:0]: HRS[5:0] */
	if (Tempax < Tempcx) /* HRE < HRS */
		Temp2 |= 0x40; /* Temp2 + 0x40 */

	Temp2 &= 0xFF;
	Tempax = (unsigned char)Temp2; /* Tempax: HRE[7:0] */
	Tempax <<= 2; /* Tempax[7:2]: HRE[5:0] */
	Tempdx >>= 6; /* Tempdx[7:6]->[1:0] HRS[9:8] */
	Tempax |= Tempdx; /* HRE[5:0]HRS[9:8] */
	/* SR2F D[7:2]->HRE, D[1:0]->HRS */
	xgifb_reg_set(pVBInfo->P3c4, 0x2F, Tempax);
	xgifb_reg_and_or(pVBInfo->P3c4, 0x30, 0xE3, 00);

	/* CR10 VRS */
	Tempax = XGI_CRT1Table[index].CR[10];
	Tempbx = Tempax; /* Tempbx: VRS */
	Tempax &= 0x01; /* Tempax[0]: VRS[0] */
	xgifb_reg_or(pVBInfo->P3c4, 0x33, Tempax); /* SR33[0]->VRS[0] */
	/* CR7[2][7] VRE */
	Tempax = XGI_CRT1Table[index].CR[9];
	Tempcx = Tempbx >> 1; /* Tempcx[6:0]: VRS[7:1] */
	Tempdx = Tempax & 0x04; /* Tempdx[2]: CR7[2] */
	Tempdx <<= 5; /* Tempdx[7]: VRS[8] */
	Tempcx |= Tempdx; /* Tempcx[7:0]: VRS[8:1] */
	xgifb_reg_set(pVBInfo->P3c4, 0x34, Tempcx); /* SR34[8:1]->VRS */

	Temp1 = Tempdx; /* Temp1[7]: Tempdx[7] */
	Temp1 <<= 1; /* Temp1[8]: VRS[8] */
	Temp1 |= Tempbx; /* Temp1[8:0]: VRS[8:0] */
	Tempax &= 0x80;
	Temp2 = Tempax << 2; /* Temp2[9]: VRS[9] */
	Temp1 |= Temp2; /* Temp1[9:0]: VRS[9:0] */
	/* Tempax: SRA */
	Tempax = XGI_CRT1Table[index].CR[14];
	Tempax &= 0x08; /* Tempax[3]: VRS[3] */
	Temp2 = Tempax;
	Temp2 <<= 7; /* Temp2[10]: VRS[10] */
	Temp1 |= Temp2; /* Temp1[10:0]: VRS[10:0] */

	/* Tempax: CR11 VRE */
	Tempax = XGI_CRT1Table[index].CR[11];
	Tempax &= 0x0F; /* Tempax[3:0]: VRE[3:0] */
	/* Tempbx: SRA */
	Tempbx = XGI_CRT1Table[index].CR[14];
	Tempbx &= 0x20; /* Tempbx[5]: VRE[5] */
	Tempbx >>= 1; /* Tempbx[4]: VRE[4] */
	Tempax |= Tempbx; /* Tempax[4:0]: VRE[4:0] */
	Temp2 = Temp1 & 0x7E0; /* Temp2[10:5]: VRS[10:5] */
	Temp2 |= Tempax; /* Temp2[10:5]: VRE[10:5] */

	Temp3 = Temp1 & 0x1F; /* Temp3[4:0]: VRS[4:0] */
	if (Tempax < Temp3) /* VRE < VRS */
		Temp2 |= 0x20; /* VRE + 0x20 */

	Temp2 &= 0xFF;
	Tempax = (unsigned char)Temp2; /* Tempax: VRE[7:0] */
	Tempax <<= 2; /* Tempax[7:0]; VRE[5:0]00 */
	Temp1 &= 0x600; /* Temp1[10:9]: VRS[10:9] */
	Temp1 >>= 9; /* Temp1[1:0]: VRS[10:9] */
	Tempbx = (unsigned char)Temp1;
	Tempax |= Tempbx; /* Tempax[7:0]: VRE[5:0]VRS[10:9] */
	Tempax &= 0x7F;
	/* SR3F D[7:2]->VRE D[1:0]->VRS */
	xgifb_reg_set(pVBInfo->P3c4, 0x3F, Tempax);
}