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
struct vb_device_info {unsigned short VBInfo; } ;

/* Variables and functions */
 unsigned short DisableCRT2Display ; 
 unsigned short SetCRT2ToDualEdge ; 
 unsigned short SetSimuScanMode ; 
 unsigned short SwitchCRT2 ; 

__attribute__((used)) static unsigned char XGI_IsLCDON(struct vb_device_info *pVBInfo)
{
	unsigned short tempax;

	tempax = pVBInfo->VBInfo;
	if (tempax & SetCRT2ToDualEdge)
		return 0;
	else if (tempax & (DisableCRT2Display | SwitchCRT2 | SetSimuScanMode))
		return 1;

	return 0;
}