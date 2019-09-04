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
struct vb_device_info {int VBInfo; int /*<<< orphan*/  P3d4; } ;

/* Variables and functions */
 int SetInSlaveMode ; 
 int /*<<< orphan*/  xgifb_reg_and_or (int /*<<< orphan*/ ,int,unsigned short,unsigned short) ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,int,unsigned short) ; 

__attribute__((used)) static void XGI_SaveCRT2Info(unsigned short ModeNo,
			     struct vb_device_info *pVBInfo)
{
	unsigned short temp1, temp2;

	/* reserve CR34 for CRT1 Mode No */
	xgifb_reg_set(pVBInfo->P3d4, 0x34, ModeNo);
	temp1 = (pVBInfo->VBInfo & SetInSlaveMode) >> 8;
	temp2 = ~(SetInSlaveMode >> 8);
	xgifb_reg_and_or(pVBInfo->P3d4, 0x31, temp2, temp1);
}