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
typedef  int s64 ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int blkstol2(s64 nb)
{
	int l2nb;
	s64 mask;		/* meant to be signed */

	mask = (s64) 1 << (64 - 1);

	/* count the leading bits.
	 */
	for (l2nb = 0; l2nb < 64; l2nb++, mask >>= 1) {
		/* leading bit found.
		 */
		if (nb & mask) {
			/* determine the l2 value.
			 */
			l2nb = (64 - 1) - l2nb;

			/* check if we need to round up.
			 */
			if (~mask & nb)
				l2nb++;

			return (l2nb);
		}
	}
	assert(0);
	return 0;		/* fix compiler warning */
}