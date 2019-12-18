#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int offnum; int /*<<< orphan*/  page; int /*<<< orphan*/  blkno; } ;
struct TYPE_4__ {scalar_t__ tupstate; int nextOffset; scalar_t__ size; } ;
typedef  int /*<<< orphan*/  SpGistState ;
typedef  TYPE_1__* SpGistLeafTuple ;
typedef  TYPE_2__ SPPageDesc ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  ItemIdData ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int BLCKSZ ; 
 int /*<<< orphan*/  ERROR ; 
 int FirstOffsetNumber ; 
 int InvalidOffsetNumber ; 
 scalar_t__ PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,int) ; 
 int PageGetMaxOffsetNumber (int /*<<< orphan*/ ) ; 
 scalar_t__ SPGIST_DEAD ; 
 scalar_t__ SPGIST_LIVE ; 
 scalar_t__ SpGistBlockIsRoot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static int
checkSplitConditions(Relation index, SpGistState *state,
					 SPPageDesc *current, int *nToSplit)
{
	int			i,
				n = 0,
				totalSize = 0;

	if (SpGistBlockIsRoot(current->blkno))
	{
		/* return impossible values to force split */
		*nToSplit = BLCKSZ;
		return BLCKSZ;
	}

	i = current->offnum;
	while (i != InvalidOffsetNumber)
	{
		SpGistLeafTuple it;

		Assert(i >= FirstOffsetNumber &&
			   i <= PageGetMaxOffsetNumber(current->page));
		it = (SpGistLeafTuple) PageGetItem(current->page,
										   PageGetItemId(current->page, i));
		if (it->tupstate == SPGIST_LIVE)
		{
			n++;
			totalSize += it->size + sizeof(ItemIdData);
		}
		else if (it->tupstate == SPGIST_DEAD)
		{
			/* We could see a DEAD tuple as first/only chain item */
			Assert(i == current->offnum);
			Assert(it->nextOffset == InvalidOffsetNumber);
			/* Don't count it in result, because it won't go to other page */
		}
		else
			elog(ERROR, "unexpected SPGiST tuple state: %d", it->tupstate);

		i = it->nextOffset;
	}

	*nToSplit = n;

	return totalSize;
}