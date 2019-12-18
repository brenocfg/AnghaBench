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
typedef  int uint64 ;
typedef  unsigned int uint32 ;
typedef  int /*<<< orphan*/  floating_decimal_64 ;

/* Variables and functions */
 int const DOUBLE_EXPONENT_BITS ; 
 int const DOUBLE_MANTISSA_BITS ; 
 int const UINT64CONST (int) ; 
 int copy_special_str (char*,int const,int,int) ; 
 int /*<<< orphan*/  d2d (int const,unsigned int const) ; 
 int d2d_small_int (int const,unsigned int const,int /*<<< orphan*/ *) ; 
 int double_to_bits (double) ; 
 int to_chars (int /*<<< orphan*/ ,int const,char*) ; 

int
double_to_shortest_decimal_bufn(double f, char *result)
{
	/*
	 * Step 1: Decode the floating-point number, and unify normalized and
	 * subnormal cases.
	 */
	const uint64 bits = double_to_bits(f);

	/* Decode bits into sign, mantissa, and exponent. */
	const bool	ieeeSign = ((bits >> (DOUBLE_MANTISSA_BITS + DOUBLE_EXPONENT_BITS)) & 1) != 0;
	const uint64 ieeeMantissa = bits & ((UINT64CONST(1) << DOUBLE_MANTISSA_BITS) - 1);
	const uint32 ieeeExponent = (uint32) ((bits >> DOUBLE_MANTISSA_BITS) & ((1u << DOUBLE_EXPONENT_BITS) - 1));

	/* Case distinction; exit early for the easy cases. */
	if (ieeeExponent == ((1u << DOUBLE_EXPONENT_BITS) - 1u) || (ieeeExponent == 0 && ieeeMantissa == 0))
	{
		return copy_special_str(result, ieeeSign, (ieeeExponent != 0), (ieeeMantissa != 0));
	}

	floating_decimal_64 v;
	const bool	isSmallInt = d2d_small_int(ieeeMantissa, ieeeExponent, &v);

	if (!isSmallInt)
	{
		v = d2d(ieeeMantissa, ieeeExponent);
	}

	return to_chars(v, ieeeSign, result);
}