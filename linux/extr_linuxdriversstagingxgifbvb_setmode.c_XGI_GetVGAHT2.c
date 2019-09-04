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
struct vb_device_info {int VGAVT; int VGAVDE; int RVBHCMAX; unsigned long VT; unsigned long VDE; unsigned long RVBHCFACT; unsigned long HT; } ;

/* Variables and functions */

__attribute__((used)) static unsigned short XGI_GetVGAHT2(struct vb_device_info *pVBInfo)
{
	unsigned long tempax, tempbx;

	tempbx = ((pVBInfo->VGAVT - pVBInfo->VGAVDE) * pVBInfo->RVBHCMAX)
			& 0xFFFF;
	tempax = (pVBInfo->VT - pVBInfo->VDE) * pVBInfo->RVBHCFACT;
	tempax = (tempax * pVBInfo->HT) / tempbx;

	return (unsigned short)tempax;
}