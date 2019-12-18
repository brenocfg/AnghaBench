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
typedef  scalar_t__ int16 ;
struct TYPE_5__ {scalar_t__ newitemoff; scalar_t__ leftspace; int rightspace; int olddataitemstotal; size_t nsplits; size_t maxsplits; TYPE_1__* splits; int /*<<< orphan*/  minfirstrightsz; scalar_t__ is_leaf; scalar_t__ newitemsz; } ;
struct TYPE_4__ {int newitemonleft; scalar_t__ firstoldonright; scalar_t__ rightfree; scalar_t__ leftfree; scalar_t__ curdelta; } ;
typedef  scalar_t__ Size ;
typedef  scalar_t__ OffsetNumber ;
typedef  int /*<<< orphan*/  ItemPointerData ;
typedef  int /*<<< orphan*/  ItemIdData ;
typedef  int /*<<< orphan*/  IndexTupleData ;
typedef  TYPE_2__ FindSplitData ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ MAXALIGN (int) ; 
 int /*<<< orphan*/  Min (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
_bt_recsplitloc(FindSplitData *state,
				OffsetNumber firstoldonright,
				bool newitemonleft,
				int olddataitemstoleft,
				Size firstoldonrightsz)
{
	int16		leftfree,
				rightfree;
	Size		firstrightitemsz;
	bool		newitemisfirstonright;

	/* Is the new item going to be the first item on the right page? */
	newitemisfirstonright = (firstoldonright == state->newitemoff
							 && !newitemonleft);

	if (newitemisfirstonright)
		firstrightitemsz = state->newitemsz;
	else
		firstrightitemsz = firstoldonrightsz;

	/* Account for all the old tuples */
	leftfree = state->leftspace - olddataitemstoleft;
	rightfree = state->rightspace -
		(state->olddataitemstotal - olddataitemstoleft);

	/*
	 * The first item on the right page becomes the high key of the left page;
	 * therefore it counts against left space as well as right space (we
	 * cannot assume that suffix truncation will make it any smaller).  When
	 * index has included attributes, then those attributes of left page high
	 * key will be truncated leaving that page with slightly more free space.
	 * However, that shouldn't affect our ability to find valid split
	 * location, since we err in the direction of being pessimistic about free
	 * space on the left half.  Besides, even when suffix truncation of
	 * non-TID attributes occurs, the new high key often won't even be a
	 * single MAXALIGN() quantum smaller than the firstright tuple it's based
	 * on.
	 *
	 * If we are on the leaf level, assume that suffix truncation cannot avoid
	 * adding a heap TID to the left half's new high key when splitting at the
	 * leaf level.  In practice the new high key will often be smaller and
	 * will rarely be larger, but conservatively assume the worst case.
	 */
	if (state->is_leaf)
		leftfree -= (int16) (firstrightitemsz +
							 MAXALIGN(sizeof(ItemPointerData)));
	else
		leftfree -= (int16) firstrightitemsz;

	/* account for the new item */
	if (newitemonleft)
		leftfree -= (int16) state->newitemsz;
	else
		rightfree -= (int16) state->newitemsz;

	/*
	 * If we are not on the leaf level, we will be able to discard the key
	 * data from the first item that winds up on the right page.
	 */
	if (!state->is_leaf)
		rightfree += (int16) firstrightitemsz -
			(int16) (MAXALIGN(sizeof(IndexTupleData)) + sizeof(ItemIdData));

	/* Record split if legal */
	if (leftfree >= 0 && rightfree >= 0)
	{
		Assert(state->nsplits < state->maxsplits);

		/* Determine smallest firstright item size on page */
		state->minfirstrightsz = Min(state->minfirstrightsz, firstrightitemsz);

		state->splits[state->nsplits].curdelta = 0;
		state->splits[state->nsplits].leftfree = leftfree;
		state->splits[state->nsplits].rightfree = rightfree;
		state->splits[state->nsplits].firstoldonright = firstoldonright;
		state->splits[state->nsplits].newitemonleft = newitemonleft;
		state->nsplits++;
	}
}