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
typedef  int int32 ;

/* Variables and functions */
 int next ; 

__attribute__((used)) static int32
myRand(void)
{
	/*----------
	 * Compute x = (7^5 * x) mod (2^31 - 1)
	 * without overflowing 31 bits:
	 *		(2^31 - 1) = 127773 * (7^5) + 2836
	 * From "Random number generators: good ones are hard to find",
	 * Park and Miller, Communications of the ACM, vol. 31, no. 10,
	 * October 1988, p. 1195.
	 *----------
	 */
	int32		hi,
				lo,
				x;

	/* Must be in [1, 0x7ffffffe] range at this point. */
	hi = next / 127773;
	lo = next % 127773;
	x = 16807 * lo - 2836 * hi;
	if (x < 0)
		x += 0x7fffffff;
	next = x;
	/* Transform to [0, 0x7ffffffd] range. */
	return (x - 1);
}