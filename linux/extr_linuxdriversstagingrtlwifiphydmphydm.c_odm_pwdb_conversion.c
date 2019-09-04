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
typedef  scalar_t__ u32 ;
typedef  int s32 ;

/* Variables and functions */
 int BIT (scalar_t__) ; 

s32 odm_pwdb_conversion(s32 X, u32 total_bit, u32 decimal_bit)
{
	s32 Y, integer = 0, decimal = 0;
	u32 i;

	if (X == 0)
		X = 1; /* log2(x), x can't be 0 */

	for (i = (total_bit - 1); i > 0; i--) {
		if (X & BIT(i)) {
			integer = i;
			if (i > 0) {
				/* decimal is 0.5dB*3=1.5dB~=2dB */
				decimal = (X & BIT(i - 1)) ? 2 : 0;
			}
			break;
		}
	}

	Y = 3 * (integer - decimal_bit) + decimal; /* 10*log(x)=3*log2(x), */

	return Y;
}