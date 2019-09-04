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
struct vb_device_info {int VBInfo; int /*<<< orphan*/  P3c0; int /*<<< orphan*/  P3da; } ;
struct TYPE_4__ {unsigned short Ext_ModeFlag; } ;
struct TYPE_3__ {unsigned char* ATTR; } ;

/* Variables and functions */
 unsigned short Charx8Dot ; 
 int SetCRT2ToLCD ; 
 int SetCRT2ToTV ; 
 int SetInSlaveMode ; 
 TYPE_2__* XGI330_EModeIDTable ; 
 TYPE_1__ XGI330_StandTable ; 
 int XGI_SetCRT2ToLCDA ; 
 int /*<<< orphan*/  inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void XGI_SetATTRegs(unsigned short ModeIdIndex,
			   struct vb_device_info *pVBInfo)
{
	unsigned char ARdata;
	unsigned short i, modeflag;

	modeflag = XGI330_EModeIDTable[ModeIdIndex].Ext_ModeFlag;

	for (i = 0; i <= 0x13; i++) {
		ARdata = XGI330_StandTable.ATTR[i];

		if ((modeflag & Charx8Dot) && i == 0x13) { /* ifndef Dot9 */
			if (pVBInfo->VBInfo & XGI_SetCRT2ToLCDA) {
				ARdata = 0;
			} else if ((pVBInfo->VBInfo &
				   (SetCRT2ToTV | SetCRT2ToLCD)) &&
				   (pVBInfo->VBInfo & SetInSlaveMode)) {
				ARdata = 0;
			}
		}

		inb(pVBInfo->P3da); /* reset 3da */
		outb(i, pVBInfo->P3c0); /* set index */
		outb(ARdata, pVBInfo->P3c0); /* set data */
	}

	inb(pVBInfo->P3da); /* reset 3da */
	outb(0x14, pVBInfo->P3c0); /* set index */
	outb(0x00, pVBInfo->P3c0); /* set data */
	inb(pVBInfo->P3da); /* Enable Attribute */
	outb(0x20, pVBInfo->P3c0);
}