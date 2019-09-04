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
struct vb_device_info {unsigned short VBType; int /*<<< orphan*/  Part4Port; } ;

/* Variables and functions */
 unsigned short VB_NoLCD ; 
 unsigned short VB_SIS301 ; 
 unsigned short VB_SIS301B ; 
 unsigned short VB_SIS301LV ; 
 unsigned short VB_SIS302B ; 
 unsigned short VB_SIS302LV ; 
 unsigned short VB_XGI301C ; 
 unsigned short xgifb_reg_get (int /*<<< orphan*/ ,int) ; 

void XGI_GetVBType(struct vb_device_info *pVBInfo)
{
	unsigned short flag, tempbx, tempah;

	tempbx = VB_SIS302B;
	flag = xgifb_reg_get(pVBInfo->Part4Port, 0x00);
	if (flag == 0x02)
		goto finish;

	tempbx = VB_SIS301;
	flag = xgifb_reg_get(pVBInfo->Part4Port, 0x01);
	if (flag < 0xB0)
		goto finish;

	tempbx = VB_SIS301B;
	if (flag < 0xC0)
		goto bigger_than_0xB0;

	tempbx = VB_XGI301C;
	if (flag < 0xD0)
		goto bigger_than_0xB0;

	tempbx = VB_SIS301LV;
	if (flag < 0xE0)
		goto bigger_than_0xB0;

	tempbx = VB_SIS302LV;
	tempah = xgifb_reg_get(pVBInfo->Part4Port, 0x39);
	if (tempah != 0xFF)
		tempbx = VB_XGI301C;

bigger_than_0xB0:
	if (tempbx & (VB_SIS301B | VB_SIS302B)) {
		flag = xgifb_reg_get(pVBInfo->Part4Port, 0x23);
		if (!(flag & 0x02))
			tempbx = tempbx | VB_NoLCD;
	}

finish:
	pVBInfo->VBType = tempbx;
}