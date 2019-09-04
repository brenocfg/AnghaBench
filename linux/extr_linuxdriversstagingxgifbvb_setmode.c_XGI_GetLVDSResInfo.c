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
struct vb_device_info {unsigned short VGAHDE; unsigned short HDE; unsigned short VGAVDE; unsigned short VDE; } ;
struct TYPE_4__ {unsigned short Ext_RESINFO; } ;
struct TYPE_3__ {unsigned short HTotal; unsigned short VTotal; } ;

/* Variables and functions */
 unsigned short DoubleScanMode ; 
 unsigned short HalfDCLK ; 
 TYPE_2__* XGI330_EModeIDTable ; 
 TYPE_1__* XGI330_ModeResInfo ; 

__attribute__((used)) static void XGI_GetLVDSResInfo(unsigned short ModeIdIndex,
			       struct vb_device_info *pVBInfo)
{
	unsigned short resindex, xres, yres, modeflag;

	/* si+Ext_ResInfo */
	modeflag = XGI330_EModeIDTable[ModeIdIndex].Ext_RESINFO;

	/* si+Ext_ResInfo */
	resindex = XGI330_EModeIDTable[ModeIdIndex].Ext_RESINFO;

	xres = XGI330_ModeResInfo[resindex].HTotal;
	yres = XGI330_ModeResInfo[resindex].VTotal;

	if (modeflag & HalfDCLK)
		xres <<= 1;

	if (modeflag & DoubleScanMode)
		yres <<= 1;

	if (xres == 720)
		xres = 640;

	pVBInfo->VGAHDE = xres;
	pVBInfo->HDE = xres;
	pVBInfo->VGAVDE = yres;
	pVBInfo->VDE = yres;
}