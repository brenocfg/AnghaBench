#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  nPlaceholder; int /*<<< orphan*/  nRedirection; } ;
struct TYPE_4__ {int tupstate; int /*<<< orphan*/  size; } ;
typedef  int /*<<< orphan*/  SpGistState ;
typedef  TYPE_1__* SpGistDeadTuple ;
typedef  int /*<<< orphan*/  Page ;
typedef  scalar_t__ OffsetNumber ;
typedef  int /*<<< orphan*/  Item ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int MaxIndexTuplesPerPage ; 
 scalar_t__ PageAddItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 int /*<<< orphan*/  PageIndexMultiDelete (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int SPGIST_PLACEHOLDER ; 
 int SPGIST_REDIRECT ; 
 TYPE_3__* SpGistPageGetOpaque (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmpOffsetNumbers ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  qsort (scalar_t__*,int,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* spgFormDeadTuple (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,scalar_t__) ; 

void
spgPageIndexMultiDelete(SpGistState *state, Page page,
						OffsetNumber *itemnos, int nitems,
						int firststate, int reststate,
						BlockNumber blkno, OffsetNumber offnum)
{
	OffsetNumber firstItem;
	OffsetNumber sortednos[MaxIndexTuplesPerPage];
	SpGistDeadTuple tuple = NULL;
	int			i;

	if (nitems == 0)
		return;					/* nothing to do */

	/*
	 * For efficiency we want to use PageIndexMultiDelete, which requires the
	 * targets to be listed in sorted order, so we have to sort the itemnos
	 * array.  (This also greatly simplifies the math for reinserting the
	 * replacement tuples.)  However, we must not scribble on the caller's
	 * array, so we have to make a copy.
	 */
	memcpy(sortednos, itemnos, sizeof(OffsetNumber) * nitems);
	if (nitems > 1)
		qsort(sortednos, nitems, sizeof(OffsetNumber), cmpOffsetNumbers);

	PageIndexMultiDelete(page, sortednos, nitems);

	firstItem = itemnos[0];

	for (i = 0; i < nitems; i++)
	{
		OffsetNumber itemno = sortednos[i];
		int			tupstate;

		tupstate = (itemno == firstItem) ? firststate : reststate;
		if (tuple == NULL || tuple->tupstate != tupstate)
			tuple = spgFormDeadTuple(state, tupstate, blkno, offnum);

		if (PageAddItem(page, (Item) tuple, tuple->size,
						itemno, false, false) != itemno)
			elog(ERROR, "failed to add item of size %u to SPGiST index page",
				 tuple->size);

		if (tupstate == SPGIST_REDIRECT)
			SpGistPageGetOpaque(page)->nRedirection++;
		else if (tupstate == SPGIST_PLACEHOLDER)
			SpGistPageGetOpaque(page)->nPlaceholder++;
	}
}