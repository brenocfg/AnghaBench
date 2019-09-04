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
struct vb_device_info {int VBType; int VBInfo; int SetFlag; } ;
struct TYPE_4__ {unsigned char Part4_A; unsigned char Part4_B; } ;
struct TYPE_3__ {unsigned char SR2B; unsigned char SR2C; } ;

/* Variables and functions */
 int ProgrammingCRT2 ; 
 int VB_SIS301 ; 
 int VB_SIS301B ; 
 int VB_SIS301LV ; 
 int VB_SIS302B ; 
 int VB_SIS302LV ; 
 int VB_XGI301C ; 
 int XGI_SetCRT2ToLCDA ; 
 TYPE_2__* XGI_VBVCLKData ; 
 TYPE_1__* XGI_VCLKData ; 

__attribute__((used)) static void XGI_GetVCLKLen(unsigned char tempal, unsigned char *di_0,
			   unsigned char *di_1, struct vb_device_info *pVBInfo)
{
	if (pVBInfo->VBType & (VB_SIS301 | VB_SIS301B | VB_SIS302B
			| VB_SIS301LV | VB_SIS302LV | VB_XGI301C)) {
		if (!(pVBInfo->VBInfo & XGI_SetCRT2ToLCDA) &&
		    (pVBInfo->SetFlag & ProgrammingCRT2)) {
			*di_0 = XGI_VBVCLKData[tempal].Part4_A;
			*di_1 = XGI_VBVCLKData[tempal].Part4_B;
		}
	} else {
		*di_0 = XGI_VCLKData[tempal].SR2B;
		*di_1 = XGI_VCLKData[tempal].SR2C;
	}
}