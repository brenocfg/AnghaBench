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
typedef  int u64 ;
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  do_div (int,int) ; 
 int vol_shift_64 (int,int) ; 

__attribute__((used)) static u32 vol_pow32(u32 a, int exp, u32 fwl)
{
	int i, iter;
	u32 power = 1 << fwl;
	u64 numerator;

	/* if exponent is 0, return 1 */
	if (exp == 0)
		return power;

	/* determine the number of iterations based on the exponent */
	if (exp < 0)
		iter = exp * -1;
	else
		iter = exp;

	/* mutiply a "iter" times to compute power */
	for (i = 0; i < iter; i++) {
		/*
		 * Product of 2 Qx.fwl fixed-point numbers yields a Q2*x.2*fwl
		 * Truncate product back to fwl fractional bits with rounding
		 */
		power = vol_shift_64((u64)power * a, fwl);
	}

	if (exp > 0) {
		/* if exp is positive, return the result */
		return power;
	}

	/* if exp is negative, return the multiplicative inverse */
	numerator = (u64)1 << (fwl << 1);
	do_div(numerator, power);

	return (u32)numerator;
}