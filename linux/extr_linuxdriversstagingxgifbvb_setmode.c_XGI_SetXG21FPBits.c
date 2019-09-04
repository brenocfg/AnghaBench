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
struct vb_device_info {int /*<<< orphan*/  P3c4; int /*<<< orphan*/  P3d4; } ;

/* Variables and functions */
 int /*<<< orphan*/  xgifb_reg_and_or (int /*<<< orphan*/ ,int,int,unsigned char) ; 
 unsigned char xgifb_reg_get (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void XGI_SetXG21FPBits(struct vb_device_info *pVBInfo)
{
	unsigned char temp;

	temp = xgifb_reg_get(pVBInfo->P3d4, 0x37); /* D[0] 1: 18bit */
	temp = (temp & 1) << 6;
	/* SR06[6] 18bit Dither */
	xgifb_reg_and_or(pVBInfo->P3c4, 0x06, ~0x40, temp);
	/* SR09[7] enable FP output, SR09[6] 1: sigle 18bits, 0: dual 12bits */
	xgifb_reg_and_or(pVBInfo->P3c4, 0x09, ~0xc0, temp | 0x80);
}