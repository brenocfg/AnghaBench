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
typedef  int /*<<< orphan*/  uint64 ;
typedef  scalar_t__ uint32 ;

/* Variables and functions */
 scalar_t__ const pow5Factor (int /*<<< orphan*/  const) ; 

__attribute__((used)) static inline bool
multipleOfPowerOf5(const uint64 value, const uint32 p)
{
	/*
	 * I tried a case distinction on p, but there was no performance
	 * difference.
	 */
	return pow5Factor(value) >= p;
}