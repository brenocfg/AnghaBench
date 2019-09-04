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
struct TYPE_4__ {unsigned short Ext_ModeInfo; } ;
struct TYPE_3__ {unsigned short Ext_InfoFlag; } ;

/* Variables and functions */
 unsigned short InterlaceMode ; 
 TYPE_2__* XGI330_EModeIDTable ; 
 TYPE_1__* XGI330_RefIndex ; 
 unsigned short* XGI330_ScreenOffset ; 
 unsigned short XGI_GetColorDepth (unsigned short) ; 

__attribute__((used)) static unsigned short XGI_GetOffset(unsigned short ModeNo,
				    unsigned short ModeIdIndex,
				    unsigned short RefreshRateTableIndex)
{
	unsigned short temp, colordepth, modeinfo, index, infoflag,
			ColorDepth[] = { 0x01, 0x02, 0x04 };

	modeinfo = XGI330_EModeIDTable[ModeIdIndex].Ext_ModeInfo;
	infoflag = XGI330_RefIndex[RefreshRateTableIndex].Ext_InfoFlag;

	index = (modeinfo >> 8) & 0xFF;

	temp = XGI330_ScreenOffset[index];

	if (infoflag & InterlaceMode)
		temp <<= 1;

	colordepth = XGI_GetColorDepth(ModeIdIndex);

	if ((ModeNo >= 0x7C) && (ModeNo <= 0x7E)) {
		temp = ModeNo - 0x7C;
		colordepth = ColorDepth[temp];
		temp = 0x6B;
		if (infoflag & InterlaceMode)
			temp <<= 1;
	}
	return temp * colordepth;
}