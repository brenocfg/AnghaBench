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
 int /*<<< orphan*/  Assert (int) ; 

__attribute__((used)) static inline uint64
shiftright128(const uint64 lo, const uint64 hi, const uint32 dist)
{
	/* We don't need to handle the case dist >= 64 here (see above). */
	Assert(dist < 64);
#if !defined(RYU_32_BIT_PLATFORM)
	Assert(dist > 0);
	return (hi << (64 - dist)) | (lo >> dist);
#else
	/* Avoid a 64-bit shift by taking advantage of the range of shift values. */
	Assert(dist >= 32);
	return (hi << (64 - dist)) | ((uint32) (lo >> 32) >> (dist - 32));
#endif
}