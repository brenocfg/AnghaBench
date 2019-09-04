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
struct vb_device_info {int /*<<< orphan*/  Part4Port; TYPE_1__* LCDCapList; } ;
struct TYPE_2__ {int /*<<< orphan*/  Spectrum_34; int /*<<< orphan*/  Spectrum_33; int /*<<< orphan*/  Spectrum_32; int /*<<< orphan*/  Spectrum_31; } ;

/* Variables and functions */
 unsigned short XGI_GetLCDCapPtr (struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_LongWait (struct vb_device_info*) ; 
 int /*<<< orphan*/  xgifb_reg_and (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  xgifb_reg_or (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void SetSpectrum(struct vb_device_info *pVBInfo)
{
	unsigned short index;

	index = XGI_GetLCDCapPtr(pVBInfo);

	/* disable down spectrum D[4] */
	xgifb_reg_and(pVBInfo->Part4Port, 0x30, 0x8F);
	XGI_LongWait(pVBInfo);
	xgifb_reg_or(pVBInfo->Part4Port, 0x30, 0x20); /* reset spectrum */
	XGI_LongWait(pVBInfo);

	xgifb_reg_set(pVBInfo->Part4Port, 0x31,
		      pVBInfo->LCDCapList[index].Spectrum_31);
	xgifb_reg_set(pVBInfo->Part4Port, 0x32,
		      pVBInfo->LCDCapList[index].Spectrum_32);
	xgifb_reg_set(pVBInfo->Part4Port, 0x33,
		      pVBInfo->LCDCapList[index].Spectrum_33);
	xgifb_reg_set(pVBInfo->Part4Port, 0x34,
		      pVBInfo->LCDCapList[index].Spectrum_34);
	XGI_LongWait(pVBInfo);
	xgifb_reg_or(pVBInfo->Part4Port, 0x30, 0x40); /* enable spectrum */
}