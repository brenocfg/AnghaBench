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
struct vb_device_info {int VBType; int VBInfo; int /*<<< orphan*/  Part2Port; } ;
struct XGI301C_Tap4TimingStruct {int /*<<< orphan*/ * Reg; } ;

/* Variables and functions */
 int SetCRT2ToHiVision ; 
 int SetCRT2ToTV ; 
 int VB_XGI301C ; 
 struct XGI301C_Tap4TimingStruct* XGI_GetTap4Ptr (int,struct vb_device_info*) ; 
 int /*<<< orphan*/  xgifb_reg_and_or (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,unsigned short,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void XGI_SetTap4Regs(struct vb_device_info *pVBInfo)
{
	unsigned short i, j;
	struct XGI301C_Tap4TimingStruct const *Tap4TimingPtr;

	if (!(pVBInfo->VBType & VB_XGI301C))
		return;

	Tap4TimingPtr = XGI_GetTap4Ptr(0, pVBInfo); /* Set Horizontal Scaling */
	for (i = 0x80, j = 0; i <= 0xBF; i++, j++)
		xgifb_reg_set(pVBInfo->Part2Port, i, Tap4TimingPtr->Reg[j]);

	if ((pVBInfo->VBInfo & SetCRT2ToTV) &&
	    !(pVBInfo->VBInfo & SetCRT2ToHiVision)) {
		/* Set Vertical Scaling */
		Tap4TimingPtr = XGI_GetTap4Ptr(1, pVBInfo);
		for (i = 0xC0, j = 0; i < 0xFF; i++, j++)
			xgifb_reg_set(pVBInfo->Part2Port,
				      i,
				      Tap4TimingPtr->Reg[j]);
	}

	if ((pVBInfo->VBInfo & SetCRT2ToTV) &&
	    !(pVBInfo->VBInfo & SetCRT2ToHiVision))
		/* Enable V.Scaling */
		xgifb_reg_and_or(pVBInfo->Part2Port, 0x4E, ~0x14, 0x04);
	else
		/* Enable H.Scaling */
		xgifb_reg_and_or(pVBInfo->Part2Port, 0x4E, ~0x14, 0x10);
}