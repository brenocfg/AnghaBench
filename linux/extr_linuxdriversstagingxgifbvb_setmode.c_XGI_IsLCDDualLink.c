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
struct vb_device_info {int VBInfo; int LCDInfo; } ;

/* Variables and functions */
 int SetCRT2ToLCD ; 
 int SetLCDDualLink ; 
 int XGI_SetCRT2ToLCDA ; 

__attribute__((used)) static unsigned char XGI_IsLCDDualLink(struct vb_device_info *pVBInfo)
{
	if ((pVBInfo->VBInfo & (SetCRT2ToLCD | XGI_SetCRT2ToLCDA)) &&
	    (pVBInfo->LCDInfo & SetLCDDualLink)) /* shampoo0129 */
		return 1;

	return 0;
}