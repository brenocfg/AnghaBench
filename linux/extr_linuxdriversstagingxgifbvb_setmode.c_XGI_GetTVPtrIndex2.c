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
struct vb_device_info {int TVInfo; int VBType; int VBInfo; } ;

/* Variables and functions */
 int NTSC1024x768 ; 
 int SetInSlaveMode ; 
 int TVSetPAL ; 
 int TVSetPALM ; 
 int TVSetPALN ; 
 int TVSimuMode ; 
 int VB_SIS301B ; 
 int VB_SIS301LV ; 
 int VB_SIS302B ; 
 int VB_SIS302LV ; 
 int VB_XGI301C ; 

__attribute__((used)) static void XGI_GetTVPtrIndex2(unsigned short *tempbx,
			       unsigned char *tempcl,
			       unsigned char *tempch,
			       struct vb_device_info *pVBInfo)
{
	*tempbx = 0;
	*tempcl = 0;
	*tempch = 0;

	if (pVBInfo->TVInfo & TVSetPAL)
		*tempbx = 1;

	if (pVBInfo->TVInfo & TVSetPALM)
		*tempbx = 2;

	if (pVBInfo->TVInfo & TVSetPALN)
		*tempbx = 3;

	if (pVBInfo->TVInfo & NTSC1024x768) {
		*tempbx = 4;
		if (pVBInfo->TVInfo & TVSetPALM)
			*tempbx = 5;
	}

	if (pVBInfo->VBType & (VB_SIS301B | VB_SIS302B | VB_SIS301LV
			| VB_SIS302LV | VB_XGI301C)) {
		if (!(pVBInfo->VBInfo & SetInSlaveMode) || (pVBInfo->TVInfo
				& TVSimuMode)) {
			*tempbx += 8;
			*tempcl += 1;
		}
	}

	if (pVBInfo->VBType & (VB_SIS301B | VB_SIS302B | VB_SIS301LV
			| VB_SIS302LV | VB_XGI301C))
		(*tempch)++;
}