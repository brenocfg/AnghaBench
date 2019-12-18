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

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 

__attribute__((used)) static inline uint32
decimalLength(const uint32 v)
{
	/* Function precondition: v is not a 10-digit number. */
	/* (9 digits are sufficient for round-tripping.) */
	Assert(v < 1000000000);
	if (v >= 100000000)
	{
		return 9;
	}
	if (v >= 10000000)
	{
		return 8;
	}
	if (v >= 1000000)
	{
		return 7;
	}
	if (v >= 100000)
	{
		return 6;
	}
	if (v >= 10000)
	{
		return 5;
	}
	if (v >= 1000)
	{
		return 4;
	}
	if (v >= 100)
	{
		return 3;
	}
	if (v >= 10)
	{
		return 2;
	}
	return 1;
}