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
typedef  int int32 ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 

__attribute__((used)) static inline uint32
pow5bits(const int32 e)
{
	/*
	 * This approximation works up to the point that the multiplication
	 * overflows at e = 3529.
	 *
	 * If the multiplication were done in 64 bits, it would fail at 5^4004
	 * which is just greater than 2^9297.
	 */
	Assert(e >= 0);
	Assert(e <= 3528);
	return ((((uint32) e) * 1217359) >> 19) + 1;
}