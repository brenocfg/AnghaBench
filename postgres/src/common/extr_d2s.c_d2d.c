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
typedef  scalar_t__ uint8 ;
typedef  int uint64 ;
typedef  int uint32 ;
typedef  int int32 ;
struct TYPE_3__ {int exponent; int mantissa; } ;
typedef  TYPE_1__ floating_decimal_64 ;

/* Variables and functions */
 int DOUBLE_BIAS ; 
 int const DOUBLE_MANTISSA_BITS ; 
 int DOUBLE_POW5_BITCOUNT ; 
 int DOUBLE_POW5_INV_BITCOUNT ; 
 int /*<<< orphan*/ * DOUBLE_POW5_INV_SPLIT ; 
 int /*<<< orphan*/ * DOUBLE_POW5_SPLIT ; 
 int const UINT64CONST (int) ; 
 int div10 (int) ; 
 int div100 (int) ; 
 int div5 (int const) ; 
 int log10Pow2 (int) ; 
 int log10Pow5 (int) ; 
 int mulShiftAll (int,int /*<<< orphan*/ ,int const,int*,int*,int const) ; 
 int multipleOfPowerOf2 (int const,int const) ; 
 int multipleOfPowerOf5 (int const,int const) ; 
 int pow5bits (int const) ; 

__attribute__((used)) static inline floating_decimal_64
d2d(const uint64 ieeeMantissa, const uint32 ieeeExponent)
{
	int32		e2;
	uint64		m2;

	if (ieeeExponent == 0)
	{
		/* We subtract 2 so that the bounds computation has 2 additional bits. */
		e2 = 1 - DOUBLE_BIAS - DOUBLE_MANTISSA_BITS - 2;
		m2 = ieeeMantissa;
	}
	else
	{
		e2 = ieeeExponent - DOUBLE_BIAS - DOUBLE_MANTISSA_BITS - 2;
		m2 = (UINT64CONST(1) << DOUBLE_MANTISSA_BITS) | ieeeMantissa;
	}

#if STRICTLY_SHORTEST
	const bool	even = (m2 & 1) == 0;
	const bool	acceptBounds = even;
#else
	const bool	acceptBounds = false;
#endif

	/* Step 2: Determine the interval of legal decimal representations. */
	const uint64 mv = 4 * m2;

	/* Implicit bool -> int conversion. True is 1, false is 0. */
	const uint32 mmShift = ieeeMantissa != 0 || ieeeExponent <= 1;

	/* We would compute mp and mm like this: */
	/* uint64 mp = 4 * m2 + 2; */
	/* uint64 mm = mv - 1 - mmShift; */

	/* Step 3: Convert to a decimal power base using 128-bit arithmetic. */
	uint64		vr,
				vp,
				vm;
	int32		e10;
	bool		vmIsTrailingZeros = false;
	bool		vrIsTrailingZeros = false;

	if (e2 >= 0)
	{
		/*
		 * I tried special-casing q == 0, but there was no effect on
		 * performance.
		 *
		 * This expr is slightly faster than max(0, log10Pow2(e2) - 1).
		 */
		const uint32 q = log10Pow2(e2) - (e2 > 3);
		const int32 k = DOUBLE_POW5_INV_BITCOUNT + pow5bits(q) - 1;
		const int32 i = -e2 + q + k;

		e10 = q;

		vr = mulShiftAll(m2, DOUBLE_POW5_INV_SPLIT[q], i, &vp, &vm, mmShift);

		if (q <= 21)
		{
			/*
			 * This should use q <= 22, but I think 21 is also safe. Smaller
			 * values may still be safe, but it's more difficult to reason
			 * about them.
			 *
			 * Only one of mp, mv, and mm can be a multiple of 5, if any.
			 */
			const uint32 mvMod5 = (uint32) (mv - 5 * div5(mv));

			if (mvMod5 == 0)
			{
				vrIsTrailingZeros = multipleOfPowerOf5(mv, q);
			}
			else if (acceptBounds)
			{
				/*----
				 * Same as min(e2 + (~mm & 1), pow5Factor(mm)) >= q
				 * <=> e2 + (~mm & 1) >= q && pow5Factor(mm) >= q
				 * <=> true && pow5Factor(mm) >= q, since e2 >= q.
				 *----
				 */
				vmIsTrailingZeros = multipleOfPowerOf5(mv - 1 - mmShift, q);
			}
			else
			{
				/* Same as min(e2 + 1, pow5Factor(mp)) >= q. */
				vp -= multipleOfPowerOf5(mv + 2, q);
			}
		}
	}
	else
	{
		/*
		 * This expression is slightly faster than max(0, log10Pow5(-e2) - 1).
		 */
		const uint32 q = log10Pow5(-e2) - (-e2 > 1);
		const int32 i = -e2 - q;
		const int32 k = pow5bits(i) - DOUBLE_POW5_BITCOUNT;
		const int32 j = q - k;

		e10 = q + e2;

		vr = mulShiftAll(m2, DOUBLE_POW5_SPLIT[i], j, &vp, &vm, mmShift);

		if (q <= 1)
		{
			/*
			 * {vr,vp,vm} is trailing zeros if {mv,mp,mm} has at least q
			 * trailing 0 bits.
			 */
			/* mv = 4 * m2, so it always has at least two trailing 0 bits. */
			vrIsTrailingZeros = true;
			if (acceptBounds)
			{
				/*
				 * mm = mv - 1 - mmShift, so it has 1 trailing 0 bit iff
				 * mmShift == 1.
				 */
				vmIsTrailingZeros = mmShift == 1;
			}
			else
			{
				/*
				 * mp = mv + 2, so it always has at least one trailing 0 bit.
				 */
				--vp;
			}
		}
		else if (q < 63)
		{
			/* TODO(ulfjack):Use a tighter bound here. */
			/*
			 * We need to compute min(ntz(mv), pow5Factor(mv) - e2) >= q - 1
			 */
			/* <=> ntz(mv) >= q - 1 && pow5Factor(mv) - e2 >= q - 1 */
			/* <=> ntz(mv) >= q - 1 (e2 is negative and -e2 >= q) */
			/* <=> (mv & ((1 << (q - 1)) - 1)) == 0 */

			/*
			 * We also need to make sure that the left shift does not
			 * overflow.
			 */
			vrIsTrailingZeros = multipleOfPowerOf2(mv, q - 1);
		}
	}

	/*
	 * Step 4: Find the shortest decimal representation in the interval of
	 * legal representations.
	 */
	uint32		removed = 0;
	uint8		lastRemovedDigit = 0;
	uint64		output;

	/* On average, we remove ~2 digits. */
	if (vmIsTrailingZeros || vrIsTrailingZeros)
	{
		/* General case, which happens rarely (~0.7%). */
		for (;;)
		{
			const uint64 vpDiv10 = div10(vp);
			const uint64 vmDiv10 = div10(vm);

			if (vpDiv10 <= vmDiv10)
				break;

			const uint32 vmMod10 = (uint32) (vm - 10 * vmDiv10);
			const uint64 vrDiv10 = div10(vr);
			const uint32 vrMod10 = (uint32) (vr - 10 * vrDiv10);

			vmIsTrailingZeros &= vmMod10 == 0;
			vrIsTrailingZeros &= lastRemovedDigit == 0;
			lastRemovedDigit = (uint8) vrMod10;
			vr = vrDiv10;
			vp = vpDiv10;
			vm = vmDiv10;
			++removed;
		}

		if (vmIsTrailingZeros)
		{
			for (;;)
			{
				const uint64 vmDiv10 = div10(vm);
				const uint32 vmMod10 = (uint32) (vm - 10 * vmDiv10);

				if (vmMod10 != 0)
					break;

				const uint64 vpDiv10 = div10(vp);
				const uint64 vrDiv10 = div10(vr);
				const uint32 vrMod10 = (uint32) (vr - 10 * vrDiv10);

				vrIsTrailingZeros &= lastRemovedDigit == 0;
				lastRemovedDigit = (uint8) vrMod10;
				vr = vrDiv10;
				vp = vpDiv10;
				vm = vmDiv10;
				++removed;
			}
		}

		if (vrIsTrailingZeros && lastRemovedDigit == 5 && vr % 2 == 0)
		{
			/* Round even if the exact number is .....50..0. */
			lastRemovedDigit = 4;
		}

		/*
		 * We need to take vr + 1 if vr is outside bounds or we need to round
		 * up.
		 */
		output = vr + ((vr == vm && (!acceptBounds || !vmIsTrailingZeros)) || lastRemovedDigit >= 5);
	}
	else
	{
		/*
		 * Specialized for the common case (~99.3%). Percentages below are
		 * relative to this.
		 */
		bool		roundUp = false;
		const uint64 vpDiv100 = div100(vp);
		const uint64 vmDiv100 = div100(vm);

		if (vpDiv100 > vmDiv100)
		{
			/* Optimization:remove two digits at a time(~86.2 %). */
			const uint64 vrDiv100 = div100(vr);
			const uint32 vrMod100 = (uint32) (vr - 100 * vrDiv100);

			roundUp = vrMod100 >= 50;
			vr = vrDiv100;
			vp = vpDiv100;
			vm = vmDiv100;
			removed += 2;
		}

		/*----
		 * Loop iterations below (approximately), without optimization
		 * above:
		 *
		 * 0: 0.03%, 1: 13.8%, 2: 70.6%, 3: 14.0%, 4: 1.40%, 5: 0.14%,
		 * 6+: 0.02%
		 *
		 * Loop iterations below (approximately), with optimization
		 * above:
		 *
		 * 0: 70.6%, 1: 27.8%, 2: 1.40%, 3: 0.14%, 4+: 0.02%
		 *----
		 */
		for (;;)
		{
			const uint64 vpDiv10 = div10(vp);
			const uint64 vmDiv10 = div10(vm);

			if (vpDiv10 <= vmDiv10)
				break;

			const uint64 vrDiv10 = div10(vr);
			const uint32 vrMod10 = (uint32) (vr - 10 * vrDiv10);

			roundUp = vrMod10 >= 5;
			vr = vrDiv10;
			vp = vpDiv10;
			vm = vmDiv10;
			++removed;
		}

		/*
		 * We need to take vr + 1 if vr is outside bounds or we need to round
		 * up.
		 */
		output = vr + (vr == vm || roundUp);
	}

	const int32 exp = e10 + removed;

	floating_decimal_64 fd;

	fd.exponent = exp;
	fd.mantissa = output;
	return fd;
}