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
typedef  int uint32 ;
typedef  int int32 ;

/* Variables and functions */
 int shiftright128 (int const,int const,int const) ; 
 int umul128 (int,int const,int*) ; 

__attribute__((used)) static inline uint64
mulShiftAll(uint64 m, const uint64 *const mul, const int32 j,
			uint64 *const vp, uint64 *const vm, const uint32 mmShift)
{
	m <<= 1;					/* m is maximum 55 bits */

	uint64		tmp;
	const uint64 lo = umul128(m, mul[0], &tmp);
	uint64		hi;
	const uint64 mid = tmp + umul128(m, mul[1], &hi);

	hi += mid < tmp;			/* overflow into hi */

	const uint64 lo2 = lo + mul[0];
	const uint64 mid2 = mid + mul[1] + (lo2 < lo);
	const uint64 hi2 = hi + (mid2 < mid);

	*vp = shiftright128(mid2, hi2, j - 64 - 1);

	if (mmShift == 1)
	{
		const uint64 lo3 = lo - mul[0];
		const uint64 mid3 = mid - mul[1] - (lo3 > lo);
		const uint64 hi3 = hi - (mid3 > mid);

		*vm = shiftright128(mid3, hi3, j - 64 - 1);
	}
	else
	{
		const uint64 lo3 = lo + lo;
		const uint64 mid3 = mid + mid + (lo3 < lo);
		const uint64 hi3 = hi + hi + (mid3 < mid);
		const uint64 lo4 = lo3 - mul[0];
		const uint64 mid4 = mid3 - mul[1] - (lo4 > lo3);
		const uint64 hi4 = hi3 - (mid4 > mid3);

		*vm = shiftright128(mid4, hi4, j - 64);
	}

	return shiftright128(mid, hi, j - 64 - 1);
}