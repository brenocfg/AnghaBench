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
 int /*<<< orphan*/  xgifb_reg_and (int /*<<< orphan*/ ,int,int) ; 
 unsigned char xgifb_reg_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,int,unsigned char) ; 

__attribute__((used)) static unsigned char XGI_XG27GetPSCValue(struct vb_device_info *pVBInfo)
{
	unsigned char CR4A, CRB4, temp;

	CR4A = xgifb_reg_get(pVBInfo->P3d4, 0x4A);
	xgifb_reg_and(pVBInfo->P3d4, 0x4A, ~0x0C); /* enable GPIO write */

	temp = xgifb_reg_get(pVBInfo->P3d4, 0x48);

	temp &= 0x0C;
	temp >>= 2;
	xgifb_reg_set(pVBInfo->P3d4, 0x4A, CR4A);
	CRB4 = xgifb_reg_get(pVBInfo->P3d4, 0xB4);
	temp |= ((CRB4 & 0x04) << 3);
	return temp;
}