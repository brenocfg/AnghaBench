#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64 ;
typedef  scalar_t__ uint32 ;
typedef  int int32 ;
struct TYPE_3__ {scalar_t__ mantissa; scalar_t__ exponent; } ;
typedef  TYPE_1__ floating_decimal_64 ;

/* Variables and functions */
 int DOUBLE_BIAS ; 
 int const DOUBLE_MANTISSA_BITS ; 
 int const UINT64CONST (int) ; 

__attribute__((used)) static inline bool
d2d_small_int(const uint64 ieeeMantissa,
			  const uint32 ieeeExponent,
			  floating_decimal_64 *v)
{
	const int32 e2 = (int32) ieeeExponent - DOUBLE_BIAS - DOUBLE_MANTISSA_BITS;

	/*
	 * Avoid using multiple "return false;" here since it tends to provoke the
	 * compiler into inlining multiple copies of d2d, which is undesirable.
	 */

	if (e2 >= -DOUBLE_MANTISSA_BITS && e2 <= 0)
	{
		/*----
		 * Since 2^52 <= m2 < 2^53 and 0 <= -e2 <= 52:
		 *   1 <= f = m2 / 2^-e2 < 2^53.
		 *
		 * Test if the lower -e2 bits of the significand are 0, i.e. whether
		 * the fraction is 0. We can use ieeeMantissa here, since the implied
		 * 1 bit can never be tested by this; the implied 1 can only be part
		 * of a fraction if e2 < -DOUBLE_MANTISSA_BITS which we already
		 * checked. (e.g. 0.5 gives ieeeMantissa == 0 and e2 == -53)
		 */
		const uint64 mask = (UINT64CONST(1) << -e2) - 1;
		const uint64 fraction = ieeeMantissa & mask;

		if (fraction == 0)
		{
			/*----
			 * f is an integer in the range [1, 2^53).
			 * Note: mantissa might contain trailing (decimal) 0's.
			 * Note: since 2^53 < 10^16, there is no need to adjust
			 * decimalLength().
			 */
			const uint64 m2 = (UINT64CONST(1) << DOUBLE_MANTISSA_BITS) | ieeeMantissa;

			v->mantissa = m2 >> -e2;
			v->exponent = 0;
			return true;
		}
	}

	return false;
}