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
struct TYPE_2__ {unsigned short Ext_ModeFlag; } ;

/* Variables and functions */
 unsigned short ModeEGA ; 
 unsigned short ModeTypeMask ; 
 TYPE_1__* XGI330_EModeIDTable ; 

__attribute__((used)) static unsigned short XGI_GetColorDepth(unsigned short ModeIdIndex)
{
	unsigned short ColorDepth[6] = { 1, 2, 4, 4, 6, 8 };
	short index;
	unsigned short modeflag;

	modeflag = XGI330_EModeIDTable[ModeIdIndex].Ext_ModeFlag;
	index = (modeflag & ModeTypeMask) - ModeEGA;

	if (index < 0)
		index = 0;

	return ColorDepth[index];
}