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
struct vb_device_info {int VBType; int VBInfo; int SetFlag; int /*<<< orphan*/  P3d4; int /*<<< orphan*/  Part2Port; int /*<<< orphan*/  Part1Port; int /*<<< orphan*/  P3c4; } ;

/* Variables and functions */
 unsigned short ActiveAVideo ; 
 unsigned short ActiveCRT1 ; 
 unsigned short ActiveCRT2 ; 
 unsigned short ActiveHiTV ; 
 unsigned short ActiveLCD ; 
 unsigned short ActiveSCART ; 
 unsigned short ActiveSVideo ; 
 unsigned short ActiveTV ; 
 unsigned short ActiveYPbPr ; 
 int ReserveTVOption ; 
 int SetCRT2ToHiVision ; 
 int SetCRT2ToYPbPr525750 ; 
 int VB_SIS301B ; 
 int VB_SIS301LV ; 
 int VB_SIS302B ; 
 int VB_SIS302LV ; 
 int VB_XGI301C ; 
 unsigned short XGI_ModeSwitchStatus ; 
 int /*<<< orphan*/  xgifb_reg_and_or (int /*<<< orphan*/ ,int,unsigned short,unsigned short) ; 
 unsigned short xgifb_reg_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,int,unsigned short) ; 

__attribute__((used)) static void XGI_UpdateModeInfo(struct vb_device_info *pVBInfo)
{
	unsigned short tempcl, tempch, temp, tempbl, tempax;

	if (pVBInfo->VBType & (VB_SIS301B | VB_SIS302B | VB_SIS301LV
			| VB_SIS302LV | VB_XGI301C)) {
		tempcl = 0;
		tempch = 0;
		temp = xgifb_reg_get(pVBInfo->P3c4, 0x01);

		if (!(temp & 0x20)) {
			temp = xgifb_reg_get(pVBInfo->P3d4, 0x17);
			if (temp & 0x80) {
				temp = xgifb_reg_get(pVBInfo->P3d4, 0x53);
				if (!(temp & 0x40))
					tempcl |= ActiveCRT1;
			}
		}

		temp = xgifb_reg_get(pVBInfo->Part1Port, 0x2e);
		temp &= 0x0f;

		if (!(temp == 0x08)) {
			/* Check ChannelA */
			tempax = xgifb_reg_get(pVBInfo->Part1Port, 0x13);
			if (tempax & 0x04)
				tempcl = tempcl | ActiveLCD;

			temp &= 0x05;

			if (!(tempcl & ActiveLCD)) {
				if (temp == 0x01)
					tempcl |= ActiveCRT2;
			}

			if (temp == 0x04)
				tempcl |= ActiveLCD;

			if (temp == 0x05) {
				temp = xgifb_reg_get(pVBInfo->Part2Port, 0x00);

				if (!(temp & 0x08))
					tempch |= ActiveAVideo;

				if (!(temp & 0x04))
					tempch |= ActiveSVideo;

				if (temp & 0x02)
					tempch |= ActiveSCART;

				if (pVBInfo->VBInfo & SetCRT2ToHiVision) {
					if (temp & 0x01)
						tempch |= ActiveHiTV;
				}

				if (pVBInfo->VBInfo & SetCRT2ToYPbPr525750) {
					temp = xgifb_reg_get(
							pVBInfo->Part2Port,
							0x4d);

					if (temp & 0x10)
						tempch |= ActiveYPbPr;
				}

				if (tempch != 0)
					tempcl |= ActiveTV;
			}
		}

		temp = xgifb_reg_get(pVBInfo->P3d4, 0x3d);
		if (tempcl & ActiveLCD) {
			if ((pVBInfo->SetFlag & ReserveTVOption)) {
				if (temp & ActiveTV)
					tempcl |= ActiveTV;
			}
		}
		temp = tempcl;
		tempbl = ~XGI_ModeSwitchStatus;
		xgifb_reg_and_or(pVBInfo->P3d4, 0x3d, tempbl, temp);

		if (!(pVBInfo->SetFlag & ReserveTVOption))
			xgifb_reg_set(pVBInfo->P3d4, 0x3e, tempch);
	}
}