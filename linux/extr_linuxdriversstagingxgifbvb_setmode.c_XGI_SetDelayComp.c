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
struct vb_device_info {int VBType; int VBInfo; int /*<<< orphan*/  Part1Port; } ;

/* Variables and functions */
 int SetCRT2ToDualEdge ; 
 int SetCRT2ToLCD ; 
 int SetCRT2ToRAMDAC ; 
 int SetCRT2ToTV ; 
 int VB_SIS301B ; 
 int VB_SIS301LV ; 
 int VB_SIS302B ; 
 int VB_SIS302LV ; 
 int VB_XGI301C ; 
 unsigned char XGI301LCDDelay ; 
 unsigned char XGI301TVDelay ; 
 int XGI_SetCRT2ToLCDA ; 
 unsigned char xgifb_reg_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,int,unsigned char) ; 

__attribute__((used)) static void XGI_SetDelayComp(struct vb_device_info *pVBInfo)
{
	unsigned char tempah, tempbl, tempbh;

	if (pVBInfo->VBType & (VB_SIS301B | VB_SIS302B | VB_SIS301LV
			| VB_SIS302LV | VB_XGI301C)) {
		if (pVBInfo->VBInfo & (SetCRT2ToLCD | XGI_SetCRT2ToLCDA
				| SetCRT2ToTV | SetCRT2ToRAMDAC)) {
			tempbh = 0;
			tempbl = XGI301TVDelay;

			if (pVBInfo->VBInfo & SetCRT2ToDualEdge)
				tempbl >>= 4;
			if (pVBInfo->VBInfo &
			    (SetCRT2ToLCD | XGI_SetCRT2ToLCDA)) {
				tempbh = XGI301LCDDelay;

				if (!(pVBInfo->VBInfo & XGI_SetCRT2ToLCDA))
					tempbl = tempbh;
			}

			tempbl &= 0x0F;
			tempbh &= 0xF0;
			tempah = xgifb_reg_get(pVBInfo->Part1Port, 0x2D);

			if (pVBInfo->VBInfo & (SetCRT2ToRAMDAC | SetCRT2ToLCD
					| SetCRT2ToTV)) { /* Channel B */
				tempah &= 0xF0;
				tempah |= tempbl;
			}

			if (pVBInfo->VBInfo & XGI_SetCRT2ToLCDA) {
				/* Channel A */
				tempah &= 0x0F;
				tempah |= tempbh;
			}
			xgifb_reg_set(pVBInfo->Part1Port, 0x2D, tempah);
		}
	}
}