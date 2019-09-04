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
struct TYPE_4__ {unsigned short LVDSHDE; unsigned short LVDSVDE; } ;
struct xgifb_video_info {TYPE_1__ lvds_data; } ;
struct TYPE_6__ {unsigned short Ext_RESINFO; unsigned short Ext_ModeFlag; } ;
struct TYPE_5__ {unsigned short HTotal; unsigned short VTotal; } ;

/* Variables and functions */
 unsigned short Charx8Dot ; 
 unsigned short DoubleScanMode ; 
 unsigned short HalfDCLK ; 
 TYPE_3__* XGI330_EModeIDTable ; 
 TYPE_2__* XGI330_ModeResInfo ; 
 unsigned short XGI_GetColorDepth (unsigned short) ; 

__attribute__((used)) static unsigned char XGI_XG21CheckLVDSMode(struct xgifb_video_info *xgifb_info,
					   unsigned short ModeNo,
					   unsigned short ModeIdIndex)
{
	unsigned short xres, yres, colordepth, modeflag, resindex;

	resindex = XGI330_EModeIDTable[ModeIdIndex].Ext_RESINFO;
	xres = XGI330_ModeResInfo[resindex].HTotal; /* xres->ax */
	yres = XGI330_ModeResInfo[resindex].VTotal; /* yres->bx */
	/* si+St_ModeFlag */
	modeflag = XGI330_EModeIDTable[ModeIdIndex].Ext_ModeFlag;

	if (!(modeflag & Charx8Dot)) {
		xres /= 9;
		xres *= 8;
	}

	if ((ModeNo > 0x13) && (modeflag & HalfDCLK))
		xres *= 2;

	if ((ModeNo > 0x13) && (modeflag & DoubleScanMode))
		yres *= 2;

	if (xres > xgifb_info->lvds_data.LVDSHDE)
		return 0;

	if (yres > xgifb_info->lvds_data.LVDSVDE)
		return 0;

	if (xres != xgifb_info->lvds_data.LVDSHDE ||
	    yres != xgifb_info->lvds_data.LVDSVDE) {
		colordepth = XGI_GetColorDepth(ModeIdIndex);
		if (colordepth > 2)
			return 0;
	}
	return 1;
}