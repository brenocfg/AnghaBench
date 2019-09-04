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
struct TYPE_4__ {unsigned short Ext_CRT1CRTC; } ;
struct TYPE_3__ {unsigned short* CR; } ;

/* Variables and functions */
 TYPE_2__* XGI330_RefIndex ; 
 TYPE_1__* XGI_CRT1Table ; 
 int /*<<< orphan*/  xgifb_reg_and_or (int /*<<< orphan*/ ,int,int,unsigned short) ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,int,unsigned short) ; 

__attribute__((used)) static void XGI_SetXG27CRTC(unsigned short RefreshRateTableIndex,
			    struct vb_device_info *pVBInfo)
{
	unsigned short index, Tempax, Tempbx, Tempcx;

	index = XGI330_RefIndex[RefreshRateTableIndex].Ext_CRT1CRTC;
	/* Tempax: CR4 HRS */
	Tempax = XGI_CRT1Table[index].CR[3];
	Tempbx = Tempax; /* Tempbx: HRS[7:0] */
	/* SR2E[7:0]->HRS */
	xgifb_reg_set(pVBInfo->P3c4, 0x2E, Tempax);

	/* SR0B */
	Tempax = XGI_CRT1Table[index].CR[5];
	Tempax &= 0xC0; /* Tempax[7:6]: SR0B[7:6]: HRS[9:8] */
	Tempbx |= Tempax << 2; /* Tempbx: HRS[9:0] */

	Tempax = XGI_CRT1Table[index].CR[4]; /* CR5 HRE */
	Tempax &= 0x1F; /* Tempax[4:0]: HRE[4:0] */
	Tempcx = Tempax; /* Tempcx: HRE[4:0] */

	Tempax = XGI_CRT1Table[index].CR[6]; /* SRC */
	Tempax &= 0x04; /* Tempax[2]: HRE[5] */
	Tempax <<= 3; /* Tempax[5]: HRE[5] */
	Tempcx |= Tempax; /* Tempcx[5:0]: HRE[5:0] */

	Tempbx = Tempbx & 0x3C0; /* Tempbx[9:6]: HRS[9:6] */
	Tempbx |= Tempcx; /* Tempbx: HRS[9:6]HRE[5:0] */

	/* Tempax: CR4 HRS */
	Tempax = XGI_CRT1Table[index].CR[3];
	Tempax &= 0x3F; /* Tempax: HRS[5:0] */
	if (Tempcx <= Tempax) /* HRE[5:0] < HRS[5:0] */
		Tempbx += 0x40; /* Tempbx= Tempbx + 0x40 : HRE[9:0]*/

	Tempax = XGI_CRT1Table[index].CR[5]; /* SR0B */
	Tempax &= 0xC0; /* Tempax[7:6]: SR0B[7:6]: HRS[9:8]*/
	Tempax >>= 6; /* Tempax[1:0]: HRS[9:8]*/
	Tempax |= (Tempbx << 2) & 0xFF; /* Tempax[7:2]: HRE[5:0] */
	/* SR2F [7:2][1:0]: HRE[5:0]HRS[9:8] */
	xgifb_reg_set(pVBInfo->P3c4, 0x2F, Tempax);
	xgifb_reg_and_or(pVBInfo->P3c4, 0x30, 0xE3, 00);

	/* CR10 VRS */
	Tempax = XGI_CRT1Table[index].CR[10];
	/* SR34[7:0]->VRS[7:0] */
	xgifb_reg_set(pVBInfo->P3c4, 0x34, Tempax);

	Tempcx = Tempax; /* Tempcx <= VRS[7:0] */
	/* CR7[7][2] VRS[9][8] */
	Tempax = XGI_CRT1Table[index].CR[9];
	Tempbx = Tempax; /* Tempbx <= CR07[7:0] */
	Tempax = Tempax & 0x04; /* Tempax[2]: CR7[2]: VRS[8] */
	Tempax >>= 2; /* Tempax[0]: VRS[8] */
	/* SR35[0]: VRS[8] */
	xgifb_reg_and_or(pVBInfo->P3c4, 0x35, ~0x01, Tempax);
	Tempcx |= Tempax << 8; /* Tempcx <= VRS[8:0] */
	Tempcx |= (Tempbx & 0x80) << 2; /* Tempcx <= VRS[9:0] */
	/* Tempax: SR0A */
	Tempax = XGI_CRT1Table[index].CR[14];
	Tempax &= 0x08; /* SR0A[3] VRS[10] */
	Tempcx |= Tempax << 7; /* Tempcx <= VRS[10:0] */

	/* Tempax: CR11 VRE */
	Tempax = XGI_CRT1Table[index].CR[11];
	Tempax &= 0x0F; /* Tempax[3:0]: VRE[3:0] */
	/* Tempbx: SR0A */
	Tempbx = XGI_CRT1Table[index].CR[14];
	Tempbx &= 0x20; /* Tempbx[5]: SR0A[5]: VRE[4] */
	Tempbx >>= 1; /* Tempbx[4]: VRE[4] */
	Tempax |= Tempbx; /* Tempax[4:0]: VRE[4:0] */
	Tempbx = Tempcx; /* Tempbx: VRS[10:0] */
	Tempbx &= 0x7E0; /* Tempbx[10:5]: VRS[10:5] */
	Tempbx |= Tempax; /* Tempbx: VRS[10:5]VRE[4:0] */

	if (Tempbx <= Tempcx) /* VRE <= VRS */
		Tempbx |= 0x20; /* VRE + 0x20 */

	/* Tempax: Tempax[7:0]; VRE[5:0]00 */
	Tempax = (Tempbx << 2) & 0xFF;
	/* SR3F[7:2]:VRE[5:0] */
	xgifb_reg_and_or(pVBInfo->P3c4, 0x3F, ~0xFC, Tempax);
	Tempax = Tempcx >> 8;
	/* SR35[2:0]:VRS[10:8] */
	xgifb_reg_and_or(pVBInfo->P3c4, 0x35, ~0x07, Tempax);
}