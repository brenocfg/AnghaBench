#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vb_device_info {int /*<<< orphan*/  Part2Port; } ;

/* Variables and functions */
 unsigned long* TVPhaseList ; 
 int /*<<< orphan*/  XGI_GetTVPtrIndex2 (unsigned short*,unsigned char*,unsigned char*,struct vb_device_info*) ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,int,unsigned short) ; 

__attribute__((used)) static void XGI_SetPhaseIncr(struct vb_device_info *pVBInfo)
{
	unsigned short tempbx;

	unsigned char tempcl, tempch;

	unsigned long tempData;

	XGI_GetTVPtrIndex2(&tempbx, &tempcl, &tempch, pVBInfo); /* bx, cl, ch */
	tempData = TVPhaseList[tempbx];

	xgifb_reg_set(pVBInfo->Part2Port, 0x31, (unsigned short)(tempData
			& 0x000000FF));
	xgifb_reg_set(pVBInfo->Part2Port, 0x32, (unsigned short)((tempData
			& 0x0000FF00) >> 8));
	xgifb_reg_set(pVBInfo->Part2Port, 0x33, (unsigned short)((tempData
			& 0x00FF0000) >> 16));
	xgifb_reg_set(pVBInfo->Part2Port, 0x34, (unsigned short)((tempData
			& 0xFF000000) >> 24));
}