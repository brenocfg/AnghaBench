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
struct vb_device_info {int VBInfo; scalar_t__ LCDResInfo; int LCDInfo; unsigned short VGAHDE; unsigned short HDE; unsigned short VGAVDE; unsigned short VDE; } ;
struct TYPE_4__ {unsigned short Ext_RESINFO; unsigned short Ext_ModeFlag; } ;
struct TYPE_3__ {unsigned short HTotal; unsigned short VTotal; } ;

/* Variables and functions */
 unsigned short DoubleScanMode ; 
 unsigned short HalfDCLK ; 
 int LCDNonExpanding ; 
 scalar_t__ Panel_1024x768 ; 
 scalar_t__ Panel_1280x1024 ; 
 scalar_t__ Panel_1600x1200 ; 
 int SetCRT2ToLCD ; 
 TYPE_2__* XGI330_EModeIDTable ; 
 TYPE_1__* XGI330_ModeResInfo ; 
 int XGI_LCDVESATiming ; 

__attribute__((used)) static void XGI_GetCRT2ResInfo(unsigned short ModeIdIndex,
			       struct vb_device_info *pVBInfo)
{
	unsigned short xres, yres, modeflag, resindex;

	resindex = XGI330_EModeIDTable[ModeIdIndex].Ext_RESINFO;
	xres = XGI330_ModeResInfo[resindex].HTotal; /* xres->ax */
	yres = XGI330_ModeResInfo[resindex].VTotal; /* yres->bx */
	/* si+St_ModeFlag */
	modeflag = XGI330_EModeIDTable[ModeIdIndex].Ext_ModeFlag;

	if (modeflag & HalfDCLK)
		xres *= 2;

	if (modeflag & DoubleScanMode)
		yres *= 2;

	if (!(pVBInfo->VBInfo & SetCRT2ToLCD))
		goto exit;

	if (pVBInfo->LCDResInfo == Panel_1600x1200) {
		if (!(pVBInfo->LCDInfo & XGI_LCDVESATiming)) {
			if (yres == 1024)
				yres = 1056;
		}
	}

	if (pVBInfo->LCDResInfo == Panel_1280x1024) {
		if (yres == 400)
			yres = 405;
		else if (yres == 350)
			yres = 360;

		if (pVBInfo->LCDInfo & XGI_LCDVESATiming) {
			if (yres == 360)
				yres = 375;
		}
	}

	if (pVBInfo->LCDResInfo == Panel_1024x768) {
		if (!(pVBInfo->LCDInfo & XGI_LCDVESATiming)) {
			if (!(pVBInfo->LCDInfo & LCDNonExpanding)) {
				if (yres == 350)
					yres = 357;
				else if (yres == 400)
					yres = 420;
				else if (yres == 480)
					yres = 525;
			}
		}
	}

	if (xres == 720)
		xres = 640;

exit:
	pVBInfo->VGAHDE = xres;
	pVBInfo->HDE = xres;
	pVBInfo->VGAVDE = yres;
	pVBInfo->VDE = yres;
}