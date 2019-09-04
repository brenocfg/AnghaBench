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
struct vb_device_info {int VBType; int /*<<< orphan*/  Part2Port; } ;
struct TYPE_2__ {unsigned char VB_ExtTVYFilterIndex; } ;

/* Variables and functions */
 unsigned char* NTSCYFilter1 ; 
 unsigned char* PALYFilter1 ; 
 int VB_SIS301B ; 
 int VB_SIS301LV ; 
 int VB_SIS302B ; 
 int VB_SIS302LV ; 
 int VB_XGI301C ; 
 TYPE_1__* XGI330_EModeIDTable ; 
 int /*<<< orphan*/  XGI_GetTVPtrIndex2 (unsigned short*,unsigned char*,unsigned char*,struct vb_device_info*) ; 
 unsigned char* xgifb_palmn_yfilter1 ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,int,unsigned char const) ; 
 unsigned char* xgifb_yfilter2 ; 

__attribute__((used)) static void XGI_SetYFilter(unsigned short ModeIdIndex,
			   struct vb_device_info *pVBInfo)
{
	unsigned short tempbx, index;
	unsigned char const *filterPtr;
	unsigned char tempcl, tempch, tempal;

	XGI_GetTVPtrIndex2(&tempbx, &tempcl, &tempch, pVBInfo); /* bx, cl, ch */

	switch (tempbx) {
	case 0x00:
	case 0x04:
		filterPtr = NTSCYFilter1;
		break;

	case 0x01:
		filterPtr = PALYFilter1;
		break;

	case 0x02:
	case 0x05:
	case 0x0D:
	case 0x03:
		filterPtr = xgifb_palmn_yfilter1;
		break;

	case 0x08:
	case 0x0C:
	case 0x0A:
	case 0x0B:
	case 0x09:
		filterPtr = xgifb_yfilter2;
		break;

	default:
		return;
	}

	tempal = XGI330_EModeIDTable[ModeIdIndex].VB_ExtTVYFilterIndex;
	if (tempcl == 0)
		index = tempal * 4;
	else
		index = tempal * 7;

	if ((tempcl == 0) && (tempch == 1)) {
		xgifb_reg_set(pVBInfo->Part2Port, 0x35, 0);
		xgifb_reg_set(pVBInfo->Part2Port, 0x36, 0);
		xgifb_reg_set(pVBInfo->Part2Port, 0x37, 0);
		xgifb_reg_set(pVBInfo->Part2Port, 0x38, filterPtr[index++]);
	} else {
		xgifb_reg_set(pVBInfo->Part2Port, 0x35, filterPtr[index++]);
		xgifb_reg_set(pVBInfo->Part2Port, 0x36, filterPtr[index++]);
		xgifb_reg_set(pVBInfo->Part2Port, 0x37, filterPtr[index++]);
		xgifb_reg_set(pVBInfo->Part2Port, 0x38, filterPtr[index++]);
	}

	if (pVBInfo->VBType & (VB_SIS301B | VB_SIS302B | VB_SIS301LV
			| VB_SIS302LV | VB_XGI301C)) {
		xgifb_reg_set(pVBInfo->Part2Port, 0x48, filterPtr[index++]);
		xgifb_reg_set(pVBInfo->Part2Port, 0x49, filterPtr[index++]);
		xgifb_reg_set(pVBInfo->Part2Port, 0x4A, filterPtr[index++]);
	}
}