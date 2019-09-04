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
typedef  int u8 ;
struct vb_device_info {int /*<<< orphan*/  Part1Port; } ;

/* Variables and functions */
 int /*<<< orphan*/  XGI_SetCRT2FIFO (struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_SetCRT2Offset (unsigned short,unsigned short,unsigned short,struct vb_device_info*) ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void XGI_PreSetGroup1(unsigned short ModeNo, unsigned short ModeIdIndex,
			     unsigned short RefreshRateTableIndex,
			     struct vb_device_info *pVBInfo)
{
	u8 tempcx;

	XGI_SetCRT2Offset(ModeNo, ModeIdIndex, RefreshRateTableIndex, pVBInfo);
	XGI_SetCRT2FIFO(pVBInfo);

	for (tempcx = 4; tempcx < 7; tempcx++)
		xgifb_reg_set(pVBInfo->Part1Port, tempcx, 0x0);

	xgifb_reg_set(pVBInfo->Part1Port, 0x50, 0x00);
	xgifb_reg_set(pVBInfo->Part1Port, 0x02, 0x44); /* temp 0206 */
}