#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64 ;
struct TYPE_8__ {int /*<<< orphan*/  opaque; } ;
typedef  int /*<<< orphan*/  TIDBitmap ;
typedef  int /*<<< orphan*/  ItemPointerData ;
typedef  TYPE_1__* IndexScanDesc ;
typedef  int /*<<< orphan*/  GinScanOpaque ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 scalar_t__ GinIsVoidRes (TYPE_1__*) ; 
 int /*<<< orphan*/  ItemPointerGetBlockNumber (int /*<<< orphan*/ *) ; 
 scalar_t__ ItemPointerIsLossyPage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ItemPointerSetMin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ginFreeScanKeys (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ginNewScanKey (TYPE_1__*) ; 
 int /*<<< orphan*/  scanGetItem (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  scanPendingInsert (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  startScan (TYPE_1__*) ; 
 int /*<<< orphan*/  tbm_add_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tbm_add_tuples (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 

int64
gingetbitmap(IndexScanDesc scan, TIDBitmap *tbm)
{
	GinScanOpaque so = (GinScanOpaque) scan->opaque;
	int64		ntids;
	ItemPointerData iptr;
	bool		recheck;

	/*
	 * Set up the scan keys, and check for unsatisfiable query.
	 */
	ginFreeScanKeys(so);		/* there should be no keys yet, but just to be
								 * sure */
	ginNewScanKey(scan);

	if (GinIsVoidRes(scan))
		return 0;

	ntids = 0;

	/*
	 * First, scan the pending list and collect any matching entries into the
	 * bitmap.  After we scan a pending item, some other backend could post it
	 * into the main index, and so we might visit it a second time during the
	 * main scan.  This is okay because we'll just re-set the same bit in the
	 * bitmap.  (The possibility of duplicate visits is a major reason why GIN
	 * can't support the amgettuple API, however.) Note that it would not do
	 * to scan the main index before the pending list, since concurrent
	 * cleanup could then make us miss entries entirely.
	 */
	scanPendingInsert(scan, tbm, &ntids);

	/*
	 * Now scan the main index.
	 */
	startScan(scan);

	ItemPointerSetMin(&iptr);

	for (;;)
	{
		CHECK_FOR_INTERRUPTS();

		if (!scanGetItem(scan, iptr, &iptr, &recheck))
			break;

		if (ItemPointerIsLossyPage(&iptr))
			tbm_add_page(tbm, ItemPointerGetBlockNumber(&iptr));
		else
			tbm_add_tuples(tbm, &iptr, 1, recheck);
		ntids++;
	}

	return ntids;
}