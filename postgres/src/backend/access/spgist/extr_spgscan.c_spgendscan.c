#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ numberOfOrderBys; TYPE_2__* xs_orderbynulls; TYPE_2__* xs_orderbyvals; int /*<<< orphan*/  opaque; } ;
struct TYPE_6__ {TYPE_2__* deadTupleStorage; } ;
struct TYPE_7__ {struct TYPE_7__* infDistances; struct TYPE_7__* zeroDistances; struct TYPE_7__* nonNullOrderByOffsets; struct TYPE_7__* orderByTypes; TYPE_1__ state; struct TYPE_7__* keyData; int /*<<< orphan*/  traversalCxt; int /*<<< orphan*/  tempCxt; } ;
typedef  TYPE_2__* SpGistScanOpaque ;
typedef  TYPE_3__* IndexScanDesc ;

/* Variables and functions */
 int /*<<< orphan*/  MemoryContextDelete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (TYPE_2__*) ; 

void
spgendscan(IndexScanDesc scan)
{
	SpGistScanOpaque so = (SpGistScanOpaque) scan->opaque;

	MemoryContextDelete(so->tempCxt);
	MemoryContextDelete(so->traversalCxt);

	if (so->keyData)
		pfree(so->keyData);

	if (so->state.deadTupleStorage)
		pfree(so->state.deadTupleStorage);

	if (scan->numberOfOrderBys > 0)
	{
		pfree(so->orderByTypes);
		pfree(so->nonNullOrderByOffsets);
		pfree(so->zeroDistances);
		pfree(so->infDistances);
		pfree(scan->xs_orderbyvals);
		pfree(scan->xs_orderbynulls);
	}

	pfree(so);
}