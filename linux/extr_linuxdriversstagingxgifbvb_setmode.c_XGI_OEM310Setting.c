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
struct vb_device_info {int VBInfo; int VBType; } ;

/* Variables and functions */
 int SetCRT2ToLCD ; 
 int SetCRT2ToTV ; 
 int VB_SIS301 ; 
 int /*<<< orphan*/  XGI_SetAntiFlicker (struct vb_device_info*) ; 
 int XGI_SetCRT2ToLCDA ; 
 int /*<<< orphan*/  XGI_SetDelayComp (struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_SetEdgeEnhance (struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_SetLCDCap (struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_SetPhaseIncr (struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_SetYFilter (unsigned short,struct vb_device_info*) ; 

__attribute__((used)) static void XGI_OEM310Setting(unsigned short ModeIdIndex,
			      struct vb_device_info *pVBInfo)
{
	XGI_SetDelayComp(pVBInfo);

	if (pVBInfo->VBInfo & (SetCRT2ToLCD | XGI_SetCRT2ToLCDA))
		XGI_SetLCDCap(pVBInfo);

	if (pVBInfo->VBInfo & SetCRT2ToTV) {
		XGI_SetPhaseIncr(pVBInfo);
		XGI_SetYFilter(ModeIdIndex, pVBInfo);
		XGI_SetAntiFlicker(pVBInfo);

		if (pVBInfo->VBType & VB_SIS301)
			XGI_SetEdgeEnhance(pVBInfo);
	}
}