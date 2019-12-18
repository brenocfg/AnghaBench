#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  distances ;
struct TYPE_6__ {double value; int isnull; } ;
struct TYPE_5__ {size_t nPtrs; int* recheck; int* recheckDistances; int numberOfOrderBys; scalar_t__ numberOfNonNullOrderBys; int* nonNullOrderByOffsets; int /*<<< orphan*/  indexTupDesc; int /*<<< orphan*/ * reconTups; scalar_t__ want_itup; TYPE_2__** distances; int /*<<< orphan*/ * heapPtrs; } ;
typedef  TYPE_1__* SpGistScanOpaque ;
typedef  int /*<<< orphan*/ * ItemPointer ;
typedef  TYPE_2__ IndexOrderByDistance ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 size_t MaxIndexTuplesPerPage ; 
 int /*<<< orphan*/  heap_form_tuple (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 TYPE_2__* palloc (int) ; 

__attribute__((used)) static void
storeGettuple(SpGistScanOpaque so, ItemPointer heapPtr,
			  Datum leafValue, bool isnull, bool recheck, bool recheckDistances,
			  double *nonNullDistances)
{
	Assert(so->nPtrs < MaxIndexTuplesPerPage);
	so->heapPtrs[so->nPtrs] = *heapPtr;
	so->recheck[so->nPtrs] = recheck;
	so->recheckDistances[so->nPtrs] = recheckDistances;

	if (so->numberOfOrderBys > 0)
	{
		if (isnull || so->numberOfNonNullOrderBys <= 0)
			so->distances[so->nPtrs] = NULL;
		else
		{
			IndexOrderByDistance *distances =
			palloc(sizeof(distances[0]) * so->numberOfOrderBys);
			int			i;

			for (i = 0; i < so->numberOfOrderBys; i++)
			{
				int			offset = so->nonNullOrderByOffsets[i];

				if (offset >= 0)
				{
					/* Copy non-NULL distance value */
					distances[i].value = nonNullDistances[offset];
					distances[i].isnull = false;
				}
				else
				{
					/* Set distance's NULL flag. */
					distances[i].value = 0.0;
					distances[i].isnull = true;
				}
			}

			so->distances[so->nPtrs] = distances;
		}
	}

	if (so->want_itup)
	{
		/*
		 * Reconstruct index data.  We have to copy the datum out of the temp
		 * context anyway, so we may as well create the tuple here.
		 */
		so->reconTups[so->nPtrs] = heap_form_tuple(so->indexTupDesc,
												   &leafValue,
												   &isnull);
	}
	so->nPtrs++;
}