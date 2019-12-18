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
pow5Factor(uint32 value)
{
	uint32		count = 0;

	for (;;)
	{
		Assert(value != 0);
		const uint32 q = value / 5;
		const uint32 r = value % 5;

		if (r != 0)
			break;

		value = q;
		++count;
	}
	return count;
}