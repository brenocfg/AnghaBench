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
struct vb_device_info {int TVInfo; int /*<<< orphan*/  Part2Port; } ;

/* Variables and functions */
 unsigned char* TVAntiFlickList ; 
 int TVSetYPbPr525p ; 
 int TVSetYPbPr750p ; 
 unsigned short XGI_GetTVPtrIndex (struct vb_device_info*) ; 
 int /*<<< orphan*/  xgifb_reg_and_or (int /*<<< orphan*/ ,int,int,unsigned char) ; 

__attribute__((used)) static void XGI_SetAntiFlicker(struct vb_device_info *pVBInfo)
{
	unsigned short tempbx;

	unsigned char tempah;

	if (pVBInfo->TVInfo & (TVSetYPbPr525p | TVSetYPbPr750p))
		return;

	tempbx = XGI_GetTVPtrIndex(pVBInfo);
	tempbx &= 0xFE;
	tempah = TVAntiFlickList[tempbx];
	tempah <<= 4;

	xgifb_reg_and_or(pVBInfo->Part2Port, 0x0A, 0x8F, tempah);
}