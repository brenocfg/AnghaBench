#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64 ;
struct TYPE_5__ {int nbytes; unsigned char* bytes; int /*<<< orphan*/  first; } ;
typedef  int /*<<< orphan*/  ItemPointerData ;
typedef  int /*<<< orphan*/ * ItemPointer ;
typedef  TYPE_1__ GinPostingList ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 TYPE_1__* GinNextPostingListSegment (TYPE_1__*) ; 
 int /*<<< orphan*/  ItemPointerGetOffsetNumber (int /*<<< orphan*/ *) ; 
 int OffsetNumberIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ decode_varbyte (unsigned char**) ; 
 scalar_t__ ginCompareItemPointers (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  itemptr_to_uint64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * palloc (int) ; 
 int /*<<< orphan*/ * repalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  uint64_to_itemptr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

ItemPointer
ginPostingListDecodeAllSegments(GinPostingList *segment, int len, int *ndecoded_out)
{
	ItemPointer result;
	int			nallocated;
	uint64		val;
	char	   *endseg = ((char *) segment) + len;
	int			ndecoded;
	unsigned char *ptr;
	unsigned char *endptr;

	/*
	 * Guess an initial size of the array.
	 */
	nallocated = segment->nbytes * 2 + 1;
	result = palloc(nallocated * sizeof(ItemPointerData));

	ndecoded = 0;
	while ((char *) segment < endseg)
	{
		/* enlarge output array if needed */
		if (ndecoded >= nallocated)
		{
			nallocated *= 2;
			result = repalloc(result, nallocated * sizeof(ItemPointerData));
		}

		/* copy the first item */
		Assert(OffsetNumberIsValid(ItemPointerGetOffsetNumber(&segment->first)));
		Assert(ndecoded == 0 || ginCompareItemPointers(&segment->first, &result[ndecoded - 1]) > 0);
		result[ndecoded] = segment->first;
		ndecoded++;

		val = itemptr_to_uint64(&segment->first);
		ptr = segment->bytes;
		endptr = segment->bytes + segment->nbytes;
		while (ptr < endptr)
		{
			/* enlarge output array if needed */
			if (ndecoded >= nallocated)
			{
				nallocated *= 2;
				result = repalloc(result, nallocated * sizeof(ItemPointerData));
			}

			val += decode_varbyte(&ptr);

			uint64_to_itemptr(val, &result[ndecoded]);
			ndecoded++;
		}
		segment = GinNextPostingListSegment(segment);
	}

	if (ndecoded_out)
		*ndecoded_out = ndecoded;
	return result;
}