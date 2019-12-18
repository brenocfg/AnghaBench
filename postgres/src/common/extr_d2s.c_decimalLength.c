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
typedef  long uint64 ;
typedef  int uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 

__attribute__((used)) static inline uint32
decimalLength(const uint64 v)
{
	/* This is slightly faster than a loop. */
	/* The average output length is 16.38 digits, so we check high-to-low. */
	/* Function precondition: v is not an 18, 19, or 20-digit number. */
	/* (17 digits are sufficient for round-tripping.) */
	Assert(v < 100000000000000000L);
	if (v >= 10000000000000000L)
	{
		return 17;
	}
	if (v >= 1000000000000000L)
	{
		return 16;
	}
	if (v >= 100000000000000L)
	{
		return 15;
	}
	if (v >= 10000000000000L)
	{
		return 14;
	}
	if (v >= 1000000000000L)
	{
		return 13;
	}
	if (v >= 100000000000L)
	{
		return 12;
	}
	if (v >= 10000000000L)
	{
		return 11;
	}
	if (v >= 1000000000L)
	{
		return 10;
	}
	if (v >= 100000000L)
	{
		return 9;
	}
	if (v >= 10000000L)
	{
		return 8;
	}
	if (v >= 1000000L)
	{
		return 7;
	}
	if (v >= 100000L)
	{
		return 6;
	}
	if (v >= 10000L)
	{
		return 5;
	}
	if (v >= 1000L)
	{
		return 4;
	}
	if (v >= 100L)
	{
		return 3;
	}
	if (v >= 10L)
	{
		return 2;
	}
	return 1;
}