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
struct vb_device_info {int VBInfo; int /*<<< orphan*/  Part1Port; } ;

/* Variables and functions */
 int SetInSlaveMode ; 
 unsigned short XGI_GetOffset (unsigned short,unsigned short,unsigned short) ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,int,unsigned char) ; 

__attribute__((used)) static void XGI_SetCRT2Offset(unsigned short ModeNo,
			      unsigned short ModeIdIndex,
			      unsigned short RefreshRateTableIndex,
			      struct vb_device_info *pVBInfo)
{
	unsigned short offset;
	unsigned char temp;

	if (pVBInfo->VBInfo & SetInSlaveMode)
		return;

	offset = XGI_GetOffset(ModeNo, ModeIdIndex, RefreshRateTableIndex);
	temp = (unsigned char)(offset & 0xFF);
	xgifb_reg_set(pVBInfo->Part1Port, 0x07, temp);
	temp = (unsigned char)((offset & 0xFF00) >> 8);
	xgifb_reg_set(pVBInfo->Part1Port, 0x09, temp);
	temp = (unsigned char)(((offset >> 3) & 0xFF) + 1);
	xgifb_reg_set(pVBInfo->Part1Port, 0x03, temp);
}