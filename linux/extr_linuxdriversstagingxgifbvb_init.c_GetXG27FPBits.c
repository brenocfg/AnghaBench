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
 int /*<<< orphan*/  xgifb_reg_and_or (int /*<<< orphan*/ ,int,int,int) ; 
 unsigned char xgifb_reg_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,int,unsigned char) ; 

__attribute__((used)) static unsigned char GetXG27FPBits(struct vb_device_info *pVBInfo)
{
	unsigned char CR4A, temp;

	CR4A = xgifb_reg_get(pVBInfo->P3d4, 0x4A);
	/* enable GPIOA/B/C read */
	xgifb_reg_and_or(pVBInfo->P3d4, 0x4A, ~0x03, 0x03);
	temp = xgifb_reg_get(pVBInfo->P3d4, 0x48);
	if (temp > 2)
		temp = ((temp & 0x04) >> 1) | ((~temp) & 0x01);

	xgifb_reg_set(pVBInfo->P3d4, 0x4A, CR4A);

	return temp;
}