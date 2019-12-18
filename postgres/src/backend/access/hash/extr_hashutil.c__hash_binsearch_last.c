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
typedef  scalar_t__ uint32 ;
typedef  int /*<<< orphan*/  Page ;
typedef  int OffsetNumber ;
typedef  scalar_t__ IndexTuple ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int FirstOffsetNumber ; 
 int /*<<< orphan*/  OffsetNumberIsValid (int) ; 
 scalar_t__ PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,int) ; 
 int PageGetMaxOffsetNumber (int /*<<< orphan*/ ) ; 
 scalar_t__ _hash_get_indextuple_hashkey (scalar_t__) ; 

OffsetNumber
_hash_binsearch_last(Page page, uint32 hash_value)
{
	OffsetNumber upper;
	OffsetNumber lower;

	/* Loop invariant: lower <= desired place <= upper */
	upper = PageGetMaxOffsetNumber(page);
	lower = FirstOffsetNumber - 1;

	while (upper > lower)
	{
		IndexTuple	itup;
		OffsetNumber off;
		uint32		hashkey;

		off = (upper + lower + 1) / 2;
		Assert(OffsetNumberIsValid(off));

		itup = (IndexTuple) PageGetItem(page, PageGetItemId(page, off));
		hashkey = _hash_get_indextuple_hashkey(itup);
		if (hashkey > hash_value)
			upper = off - 1;
		else
			lower = off;
	}

	return lower;
}