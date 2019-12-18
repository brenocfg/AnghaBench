#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  xs_snapshot; int /*<<< orphan*/  indexRelation; scalar_t__ xs_hitup; int /*<<< orphan*/  xs_recheck; int /*<<< orphan*/  xs_heaptid; scalar_t__ xs_want_itup; int /*<<< orphan*/  opaque; } ;
struct TYPE_6__ {size_t iPtr; size_t nPtrs; scalar_t__ numberOfOrderBys; scalar_t__* reconTups; scalar_t__ want_itup; scalar_t__* distances; int /*<<< orphan*/ * recheckDistances; int /*<<< orphan*/  orderByTypes; int /*<<< orphan*/ * recheck; int /*<<< orphan*/ * heapPtrs; } ;
typedef  TYPE_1__* SpGistScanOpaque ;
typedef  scalar_t__ ScanDirection ;
typedef  TYPE_2__* IndexScanDesc ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ ForwardScanDirection ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  index_store_float8_orderby_distances (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (scalar_t__) ; 
 int /*<<< orphan*/  spgWalk (int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  storeGettuple ; 

bool
spggettuple(IndexScanDesc scan, ScanDirection dir)
{
	SpGistScanOpaque so = (SpGistScanOpaque) scan->opaque;

	if (dir != ForwardScanDirection)
		elog(ERROR, "SP-GiST only supports forward scan direction");

	/* Copy want_itup to *so so we don't need to pass it around separately */
	so->want_itup = scan->xs_want_itup;

	for (;;)
	{
		if (so->iPtr < so->nPtrs)
		{
			/* continuing to return reported tuples */
			scan->xs_heaptid = so->heapPtrs[so->iPtr];
			scan->xs_recheck = so->recheck[so->iPtr];
			scan->xs_hitup = so->reconTups[so->iPtr];

			if (so->numberOfOrderBys > 0)
				index_store_float8_orderby_distances(scan, so->orderByTypes,
													 so->distances[so->iPtr],
													 so->recheckDistances[so->iPtr]);
			so->iPtr++;
			return true;
		}

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

		spgWalk(scan->indexRelation, so, false, storeGettuple,
				scan->xs_snapshot);

		if (so->nPtrs == 0)
			break;				/* must have completed scan */
	}

	return false;
}