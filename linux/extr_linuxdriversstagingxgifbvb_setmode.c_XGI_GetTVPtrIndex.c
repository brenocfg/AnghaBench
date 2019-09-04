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
struct vb_device_info {int TVInfo; } ;

/* Variables and functions */
 int TVSetHiVision ; 
 int TVSetPAL ; 
 int TVSetYPbPr525i ; 
 int TVSetYPbPr525p ; 
 int TVSetYPbPr750p ; 
 int TVSimuMode ; 

__attribute__((used)) static unsigned short XGI_GetTVPtrIndex(struct vb_device_info *pVBInfo)
{
	unsigned short tempbx = 0;

	if (pVBInfo->TVInfo & TVSetPAL)
		tempbx = 2;
	if (pVBInfo->TVInfo & TVSetHiVision)
		tempbx = 4;
	if (pVBInfo->TVInfo & TVSetYPbPr525i)
		tempbx = 6;
	if (pVBInfo->TVInfo & TVSetYPbPr525p)
		tempbx = 8;
	if (pVBInfo->TVInfo & TVSetYPbPr750p)
		tempbx = 10;
	if (pVBInfo->TVInfo & TVSimuMode)
		tempbx++;

	return tempbx;
}