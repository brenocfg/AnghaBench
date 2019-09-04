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
struct vb_device_info {int VBType; int VBInfo; int /*<<< orphan*/  Part4Port; TYPE_1__* LCDCapList; } ;
struct TYPE_2__ {unsigned short LCD_Capability; } ;

/* Variables and functions */
 int EnablePLLSPLOW ; 
 unsigned short EnableSpectrum ; 
 int EnableVBCLKDRVLOW ; 
 int SetCRT2ToLCD ; 
 int /*<<< orphan*/  SetSpectrum (struct vb_device_info*) ; 
 int VB_SIS301B ; 
 int VB_SIS301LV ; 
 int VB_SIS302B ; 
 int VB_SIS302LV ; 
 int VB_XGI301C ; 
 size_t XGI_GetLCDCapPtr (struct vb_device_info*) ; 
 int XGI_SetCRT2ToLCDA ; 
 int /*<<< orphan*/  XGI_SetLCDCap_A (unsigned short,struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_SetLCDCap_B (unsigned short,struct vb_device_info*) ; 
 int /*<<< orphan*/  xgifb_reg_and_or (int /*<<< orphan*/ ,int,int,unsigned short) ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,int,unsigned char) ; 

__attribute__((used)) static void XGI_SetLCDCap(struct vb_device_info *pVBInfo)
{
	unsigned short tempcx;

	tempcx = pVBInfo->LCDCapList[XGI_GetLCDCapPtr(pVBInfo)].LCD_Capability;

	if (pVBInfo->VBType & (VB_SIS301B | VB_SIS302B | VB_SIS301LV |
		VB_SIS302LV | VB_XGI301C)) {
		if (pVBInfo->VBType &
		    (VB_SIS301LV | VB_SIS302LV | VB_XGI301C)) {
			/* Set 301LV Capability */
			xgifb_reg_set(pVBInfo->Part4Port, 0x24,
				      (unsigned char)(tempcx & 0x1F));
		}
		/* VB Driving */
		xgifb_reg_and_or(pVBInfo->Part4Port, 0x0D,
				 ~((EnableVBCLKDRVLOW | EnablePLLSPLOW) >> 8),
				 (unsigned short)((tempcx & (EnableVBCLKDRVLOW |
				 EnablePLLSPLOW)) >> 8));

		if (pVBInfo->VBInfo & SetCRT2ToLCD)
			XGI_SetLCDCap_B(tempcx, pVBInfo);
		else if (pVBInfo->VBInfo & XGI_SetCRT2ToLCDA)
			XGI_SetLCDCap_A(tempcx, pVBInfo);

		if (pVBInfo->VBType & (VB_SIS302LV | VB_XGI301C)) {
			if (tempcx & EnableSpectrum)
				SetSpectrum(pVBInfo);
		}
	} else {
		/* LVDS,CH7017 */
		XGI_SetLCDCap_A(tempcx, pVBInfo);
	}
}