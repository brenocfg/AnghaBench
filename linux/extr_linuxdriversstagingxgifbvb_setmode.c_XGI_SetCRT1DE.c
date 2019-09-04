#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vb_device_info {int /*<<< orphan*/  P3d4; } ;
struct TYPE_6__ {unsigned short Ext_RESINFO; unsigned short Ext_ModeFlag; } ;
struct TYPE_5__ {unsigned short HTotal; unsigned short VTotal; } ;
struct TYPE_4__ {unsigned short Ext_InfoFlag; } ;

/* Variables and functions */
 unsigned short DoubleScanMode ; 
 unsigned short HalfDCLK ; 
 unsigned short InterlaceMode ; 
 TYPE_3__* XGI330_EModeIDTable ; 
 TYPE_2__* XGI330_ModeResInfo ; 
 TYPE_1__* XGI330_RefIndex ; 
 int /*<<< orphan*/  xgifb_reg_and_or (int /*<<< orphan*/ ,int,int,unsigned short) ; 
 void* xgifb_reg_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,int,unsigned short) ; 

__attribute__((used)) static void XGI_SetCRT1DE(unsigned short ModeIdIndex,
			  unsigned short RefreshRateTableIndex,
			  struct vb_device_info *pVBInfo)
{
	unsigned short resindex, tempax, tempbx, tempcx, temp, modeflag;

	unsigned char data;

	resindex = XGI330_EModeIDTable[ModeIdIndex].Ext_RESINFO;

	modeflag = XGI330_EModeIDTable[ModeIdIndex].Ext_ModeFlag;
	tempax = XGI330_ModeResInfo[resindex].HTotal;
	tempbx = XGI330_ModeResInfo[resindex].VTotal;

	if (modeflag & HalfDCLK)
		tempax >>= 1;

	if (modeflag & HalfDCLK)
		tempax <<= 1;

	temp = XGI330_RefIndex[RefreshRateTableIndex].Ext_InfoFlag;

	if (temp & InterlaceMode)
		tempbx >>= 1;

	if (modeflag & DoubleScanMode)
		tempbx <<= 1;

	tempcx = 8;

	tempax /= tempcx;
	tempax -= 1;
	tempbx -= 1;
	tempcx = tempax;
	temp = xgifb_reg_get(pVBInfo->P3d4, 0x11);
	data = xgifb_reg_get(pVBInfo->P3d4, 0x11);
	data &= 0x7F;
	xgifb_reg_set(pVBInfo->P3d4, 0x11, data); /* Unlock CRTC */
	xgifb_reg_set(pVBInfo->P3d4, 0x01, (unsigned short)(tempcx & 0xff));
	xgifb_reg_and_or(pVBInfo->P3d4, 0x0b, ~0x0c,
			 (unsigned short)((tempcx & 0x0ff00) >> 10));
	xgifb_reg_set(pVBInfo->P3d4, 0x12, (unsigned short)(tempbx & 0xff));
	tempax = 0;
	tempbx >>= 8;

	if (tempbx & 0x01)
		tempax |= 0x02;

	if (tempbx & 0x02)
		tempax |= 0x40;

	xgifb_reg_and_or(pVBInfo->P3d4, 0x07, ~0x42, tempax);
	data = xgifb_reg_get(pVBInfo->P3d4, 0x07);
	tempax = 0;

	if (tempbx & 0x04)
		tempax |= 0x02;

	xgifb_reg_and_or(pVBInfo->P3d4, 0x0a, ~0x02, tempax);
	xgifb_reg_set(pVBInfo->P3d4, 0x11, temp);
}