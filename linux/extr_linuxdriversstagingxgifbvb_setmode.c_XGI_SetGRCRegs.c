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
struct vb_device_info {scalar_t__ ModeType; int /*<<< orphan*/  P3ce; } ;
struct TYPE_2__ {unsigned char* GRC; } ;

/* Variables and functions */
 scalar_t__ ModeVGA ; 
 TYPE_1__ XGI330_StandTable ; 
 unsigned char xgifb_reg_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,int,unsigned char) ; 

__attribute__((used)) static void XGI_SetGRCRegs(struct vb_device_info *pVBInfo)
{
	unsigned char GRdata;
	unsigned short i;

	for (i = 0; i <= 0x08; i++) {
		/* Get GR from file */
		GRdata = XGI330_StandTable.GRC[i];
		xgifb_reg_set(pVBInfo->P3ce, i, GRdata); /* Set GR(3ce) */
	}

	if (pVBInfo->ModeType > ModeVGA) {
		GRdata = xgifb_reg_get(pVBInfo->P3ce, 0x05);
		GRdata &= 0xBF; /* 256 color disable */
		xgifb_reg_set(pVBInfo->P3ce, 0x05, GRdata);
	}
}