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
typedef  int Size ;

/* Variables and functions */
 int ALLOCSET_NUM_FREELISTS ; 
 int ALLOC_MINBITS ; 
 int /*<<< orphan*/  Assert (int) ; 
 int* LogTable256 ; 

__attribute__((used)) static inline int
AllocSetFreeIndex(Size size)
{
	int			idx;
	unsigned int t,
				tsize;

	if (size > (1 << ALLOC_MINBITS))
	{
		tsize = (size - 1) >> ALLOC_MINBITS;

		/*
		 * At this point we need to obtain log2(tsize)+1, ie, the number of
		 * not-all-zero bits at the right.  We used to do this with a
		 * shift-and-count loop, but this function is enough of a hotspot to
		 * justify micro-optimization effort.  The best approach seems to be
		 * to use a lookup table.  Note that this code assumes that
		 * ALLOCSET_NUM_FREELISTS <= 17, since we only cope with two bytes of
		 * the tsize value.
		 */
		t = tsize >> 8;
		idx = t ? LogTable256[t] + 8 : LogTable256[tsize];

		Assert(idx < ALLOCSET_NUM_FREELISTS);
	}
	else
		idx = 0;

	return idx;
}