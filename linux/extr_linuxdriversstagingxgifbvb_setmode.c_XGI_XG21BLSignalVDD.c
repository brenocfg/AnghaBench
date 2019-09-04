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
struct vb_device_info {int /*<<< orphan*/  P3d4; } ;

/* Variables and functions */
 unsigned char XG21GPIODataTransfer (unsigned char) ; 
 int /*<<< orphan*/  xgifb_reg_and (int /*<<< orphan*/ ,int,unsigned short) ; 
 int /*<<< orphan*/  xgifb_reg_and_or (int /*<<< orphan*/ ,int,int,unsigned char) ; 
 unsigned char xgifb_reg_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,int,unsigned char) ; 

__attribute__((used)) static void XGI_XG21BLSignalVDD(unsigned short tempbh, unsigned short tempbl,
				struct vb_device_info *pVBInfo)
{
	unsigned char CR4A, temp;

	CR4A = xgifb_reg_get(pVBInfo->P3d4, 0x4A);
	tempbh &= 0x23;
	tempbl &= 0x23;
	xgifb_reg_and(pVBInfo->P3d4, 0x4A, ~tempbh); /* enable GPIO write */

	if (tempbh & 0x20) {
		temp = (tempbl >> 4) & 0x02;

		/* CR B4[1] */
		xgifb_reg_and_or(pVBInfo->P3d4, 0xB4, ~0x02, temp);
	}

	temp = xgifb_reg_get(pVBInfo->P3d4, 0x48);

	temp = XG21GPIODataTransfer(temp);
	temp &= ~tempbh;
	temp |= tempbl;
	xgifb_reg_set(pVBInfo->P3d4, 0x48, temp);
}