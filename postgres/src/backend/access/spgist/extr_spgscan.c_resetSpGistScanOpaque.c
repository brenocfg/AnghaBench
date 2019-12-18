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
struct TYPE_5__ {scalar_t__ numberOfOrderBys; int nPtrs; int iPtr; scalar_t__* reconTups; scalar_t__ want_itup; scalar_t__* distances; scalar_t__ searchNonNulls; scalar_t__ searchNulls; int /*<<< orphan*/  scanQueue; int /*<<< orphan*/  traversalCxt; } ;
typedef  TYPE_1__* SpGistScanOpaque ;
typedef  int /*<<< orphan*/  MemoryContext ;

/* Variables and functions */
 int /*<<< orphan*/  MemoryContextReset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pairingheap_SpGistSearchItem_cmp ; 
 int /*<<< orphan*/  pairingheap_allocate (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  pfree (scalar_t__) ; 
 int /*<<< orphan*/  spgAddStartItem (TYPE_1__*,int) ; 

__attribute__((used)) static void
resetSpGistScanOpaque(SpGistScanOpaque so)
{
	MemoryContext oldCtx;

	MemoryContextReset(so->traversalCxt);

	oldCtx = MemoryContextSwitchTo(so->traversalCxt);

	/* initialize queue only for distance-ordered scans */
	so->scanQueue = pairingheap_allocate(pairingheap_SpGistSearchItem_cmp, so);

	if (so->searchNulls)
		/* Add a work item to scan the null index entries */
		spgAddStartItem(so, true);

	if (so->searchNonNulls)
		/* Add a work item to scan the non-null index entries */
		spgAddStartItem(so, false);

	MemoryContextSwitchTo(oldCtx);

	if (so->numberOfOrderBys > 0)
	{
		/* Must pfree distances to avoid memory leak */
		int			i;

		for (i = 0; i < so->nPtrs; i++)
			if (so->distances[i])
				pfree(so->distances[i]);
	}

	if (so->want_itup)
	{
		/* Must pfree reconstructed tuples to avoid memory leak */
		int			i;

		for (i = 0; i < so->nPtrs; i++)
			pfree(so->reconTups[i]);
	}
	so->iPtr = so->nPtrs = 0;
}