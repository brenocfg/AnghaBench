#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  ginstate; } ;
struct TYPE_11__ {int /*<<< orphan*/  t_tid; } ;
struct TYPE_10__ {int /*<<< orphan*/  nvalues; int /*<<< orphan*/  categories; int /*<<< orphan*/  keys; } ;
typedef  int /*<<< orphan*/  Page ;
typedef  scalar_t__ OffsetNumber ;
typedef  TYPE_1__ KeyArray ;
typedef  int /*<<< orphan*/  ItemPointerData ;
typedef  TYPE_2__* IndexTuple ;
typedef  int /*<<< orphan*/  GinNullCategory ;
typedef  int /*<<< orphan*/  Datum ;
typedef  TYPE_3__ BuildAccumulator ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ FirstOffsetNumber ; 
 scalar_t__ ItemPointerEquals (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ItemPointerIsValid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ItemPointerSetInvalid (int /*<<< orphan*/ *) ; 
 scalar_t__ OffsetNumberNext (scalar_t__) ; 
 int /*<<< orphan*/  PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ PageGetMaxOffsetNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addDatum (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ginInsertBAEntries (TYPE_3__*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gintuple_get_attrnum (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  gintuple_get_key (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
processPendingPage(BuildAccumulator *accum, KeyArray *ka,
				   Page page, OffsetNumber startoff)
{
	ItemPointerData heapptr;
	OffsetNumber i,
				maxoff;
	OffsetNumber attrnum;

	/* reset *ka to empty */
	ka->nvalues = 0;

	maxoff = PageGetMaxOffsetNumber(page);
	Assert(maxoff >= FirstOffsetNumber);
	ItemPointerSetInvalid(&heapptr);
	attrnum = 0;

	for (i = startoff; i <= maxoff; i = OffsetNumberNext(i))
	{
		IndexTuple	itup = (IndexTuple) PageGetItem(page, PageGetItemId(page, i));
		OffsetNumber curattnum;
		Datum		curkey;
		GinNullCategory curcategory;

		/* Check for change of heap TID or attnum */
		curattnum = gintuple_get_attrnum(accum->ginstate, itup);

		if (!ItemPointerIsValid(&heapptr))
		{
			heapptr = itup->t_tid;
			attrnum = curattnum;
		}
		else if (!(ItemPointerEquals(&heapptr, &itup->t_tid) &&
				   curattnum == attrnum))
		{
			/*
			 * ginInsertBAEntries can insert several datums per call, but only
			 * for one heap tuple and one column.  So call it at a boundary,
			 * and reset ka.
			 */
			ginInsertBAEntries(accum, &heapptr, attrnum,
							   ka->keys, ka->categories, ka->nvalues);
			ka->nvalues = 0;
			heapptr = itup->t_tid;
			attrnum = curattnum;
		}

		/* Add key to KeyArray */
		curkey = gintuple_get_key(accum->ginstate, itup, &curcategory);
		addDatum(ka, curkey, curcategory);
	}

	/* Dump out all remaining keys */
	ginInsertBAEntries(accum, &heapptr, attrnum,
					   ka->keys, ka->categories, ka->nvalues);
}