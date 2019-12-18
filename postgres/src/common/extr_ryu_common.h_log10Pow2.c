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

__attribute__((used)) static inline int32
log10Pow2(const int32 e)
{
	/*
	 * The first value this approximation fails for is 2^1651 which is just
	 * greater than 10^297.
	 */
	Assert(e >= 0);
	Assert(e <= 1650);
	return (int32) ((((uint32) e) * 78913) >> 18);
}