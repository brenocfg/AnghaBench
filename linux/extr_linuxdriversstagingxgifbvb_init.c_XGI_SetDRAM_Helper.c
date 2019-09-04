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
typedef  int u8 ;

/* Variables and functions */
 int /*<<< orphan*/  xgifb_reg_get (unsigned long,int) ; 
 int /*<<< orphan*/  xgifb_reg_set (unsigned long,int,int) ; 

__attribute__((used)) static void XGI_SetDRAM_Helper(unsigned long P3d4, u8 seed, u8 temp2, u8 reg,
			       u8 shift_factor, u8 mask1, u8 mask2)
{
	u8 j;

	for (j = 0; j < 4; j++) {
		temp2 |= (((seed >> (2 * j)) & 0x03) << shift_factor);
		xgifb_reg_set(P3d4, reg, temp2);
		xgifb_reg_get(P3d4, reg);
		temp2 &= mask1;
		temp2 += mask2;
	}
}