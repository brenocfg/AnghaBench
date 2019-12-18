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

/* Variables and functions */

__attribute__((used)) static inline uint64
umul128(const uint64 a, const uint64 b, uint64 *const productHi)
{
	/*
	 * The casts here help MSVC to avoid calls to the __allmul library
	 * function.
	 */
	const uint32 aLo = (uint32) a;
	const uint32 aHi = (uint32) (a >> 32);
	const uint32 bLo = (uint32) b;
	const uint32 bHi = (uint32) (b >> 32);

	const uint64 b00 = (uint64) aLo * bLo;
	const uint64 b01 = (uint64) aLo * bHi;
	const uint64 b10 = (uint64) aHi * bLo;
	const uint64 b11 = (uint64) aHi * bHi;

	const uint32 b00Lo = (uint32) b00;
	const uint32 b00Hi = (uint32) (b00 >> 32);

	const uint64 mid1 = b10 + b00Hi;
	const uint32 mid1Lo = (uint32) (mid1);
	const uint32 mid1Hi = (uint32) (mid1 >> 32);

	const uint64 mid2 = b01 + mid1Lo;
	const uint32 mid2Lo = (uint32) (mid2);
	const uint32 mid2Hi = (uint32) (mid2 >> 32);

	const uint64 pHi = b11 + mid1Hi + mid2Hi;
	const uint64 pLo = ((uint64) mid2Lo << 32) + b00Lo;

	*productHi = pHi;
	return pLo;
}