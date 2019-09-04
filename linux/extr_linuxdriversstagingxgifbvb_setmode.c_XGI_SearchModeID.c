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
struct TYPE_2__ {unsigned short Ext_ModeID; } ;

/* Variables and functions */
 TYPE_1__* XGI330_EModeIDTable ; 

unsigned char XGI_SearchModeID(unsigned short ModeNo,
			       unsigned short *ModeIdIndex)
{
	for (*ModeIdIndex = 0;; (*ModeIdIndex)++) {
		if (XGI330_EModeIDTable[*ModeIdIndex].Ext_ModeID == ModeNo)
			break;
		if (XGI330_EModeIDTable[*ModeIdIndex].Ext_ModeID == 0xFF)
			return 0;
	}

	return 1;
}