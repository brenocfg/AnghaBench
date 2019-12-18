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
 int /*<<< orphan*/  Assert (int) ; 
 int const PG_UINT32_MAX ; 

__attribute__((used)) static inline uint32
mulShift(const uint32 m, const uint64 factor, const int32 shift)
{
	/*
	 * The casts here help MSVC to avoid calls to the __allmul library
	 * function.
	 */
	const uint32 factorLo = (uint32) (factor);
	const uint32 factorHi = (uint32) (factor >> 32);
	const uint64 bits0 = (uint64) m * factorLo;
	const uint64 bits1 = (uint64) m * factorHi;

	Assert(shift > 32);

#ifdef RYU_32_BIT_PLATFORM

	/*
	 * On 32-bit platforms we can avoid a 64-bit shift-right since we only
	 * need the upper 32 bits of the result and the shift value is > 32.
	 */
	const uint32 bits0Hi = (uint32) (bits0 >> 32);
	uint32		bits1Lo = (uint32) (bits1);
	uint32		bits1Hi = (uint32) (bits1 >> 32);

	bits1Lo += bits0Hi;
	bits1Hi += (bits1Lo < bits0Hi);

	const int32 s = shift - 32;

	return (bits1Hi << (32 - s)) | (bits1Lo >> s);

#else							/* RYU_32_BIT_PLATFORM */

	const uint64 sum = (bits0 >> 32) + bits1;
	const uint64 shiftedSum = sum >> (shift - 32);

	Assert(shiftedSum <= PG_UINT32_MAX);
	return (uint32) shiftedSum;

#endif							/* RYU_32_BIT_PLATFORM */
}