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
typedef  scalar_t__ int32 ;
typedef  scalar_t__ OffsetNumber ;
typedef  int /*<<< orphan*/  ItemPointer ;
typedef  int /*<<< orphan*/  GinNullCategory ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  BuildAccumulator ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ FirstOffsetNumber ; 
 scalar_t__ ItemPointerIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ginInsertBAEntry (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ginInsertBAEntries(BuildAccumulator *accum,
				   ItemPointer heapptr, OffsetNumber attnum,
				   Datum *entries, GinNullCategory *categories,
				   int32 nentries)
{
	uint32		step = nentries;

	if (nentries <= 0)
		return;

	Assert(ItemPointerIsValid(heapptr) && attnum >= FirstOffsetNumber);

	/*
	 * step will contain largest power of 2 and <= nentries
	 */
	step |= (step >> 1);
	step |= (step >> 2);
	step |= (step >> 4);
	step |= (step >> 8);
	step |= (step >> 16);
	step >>= 1;
	step++;

	while (step > 0)
	{
		int			i;

		for (i = step - 1; i < nentries && i >= 0; i += step << 1 /* *2 */ )
			ginInsertBAEntry(accum, heapptr, attnum,
							 entries[i], categories[i]);

		step >>= 1;				/* /2 */
	}
}