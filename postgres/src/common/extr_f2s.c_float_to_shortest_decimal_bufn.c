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
typedef  int uint32 ;
typedef  int /*<<< orphan*/  floating_decimal_32 ;

/* Variables and functions */
 int const FLOAT_EXPONENT_BITS ; 
 int const FLOAT_MANTISSA_BITS ; 
 int copy_special_str (char*,int const,int,int) ; 
 int /*<<< orphan*/  f2d (int const,int const) ; 
 int f2d_small_int (int const,int const,int /*<<< orphan*/ *) ; 
 int float_to_bits (float) ; 
 int to_chars (int /*<<< orphan*/ ,int const,char*) ; 

int
float_to_shortest_decimal_bufn(float f, char *result)
{
	/*
	 * Step 1: Decode the floating-point number, and unify normalized and
	 * subnormal cases.
	 */
	const uint32 bits = float_to_bits(f);

	/* Decode bits into sign, mantissa, and exponent. */
	const bool	ieeeSign = ((bits >> (FLOAT_MANTISSA_BITS + FLOAT_EXPONENT_BITS)) & 1) != 0;
	const uint32 ieeeMantissa = bits & ((1u << FLOAT_MANTISSA_BITS) - 1);
	const uint32 ieeeExponent = (bits >> FLOAT_MANTISSA_BITS) & ((1u << FLOAT_EXPONENT_BITS) - 1);

	/* Case distinction; exit early for the easy cases. */
	if (ieeeExponent == ((1u << FLOAT_EXPONENT_BITS) - 1u) || (ieeeExponent == 0 && ieeeMantissa == 0))
	{
		return copy_special_str(result, ieeeSign, (ieeeExponent != 0), (ieeeMantissa != 0));
	}

	floating_decimal_32 v;
	const bool	isSmallInt = f2d_small_int(ieeeMantissa, ieeeExponent, &v);

	if (!isSmallInt)
	{
		v = f2d(ieeeMantissa, ieeeExponent);
	}

	return to_chars(v, ieeeSign, result);
}