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
typedef  scalar_t__ __u64 ;

/* Variables and functions */
 scalar_t__ ULONG_MAX ; 

__attribute__((used)) static inline bool rlim64_is_infinity(__u64 rlim64)
{
#if BITS_PER_LONG < 64
	return rlim64 >= ULONG_MAX;
#else
	return rlim64 == RLIM64_INFINITY;
#endif
}