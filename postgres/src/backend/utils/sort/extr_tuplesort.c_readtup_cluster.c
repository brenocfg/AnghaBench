#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tuplen ;
struct TYPE_10__ {int /*<<< orphan*/  tupDesc; TYPE_1__* indexInfo; int /*<<< orphan*/  tapeset; scalar_t__ randomAccess; } ;
typedef  TYPE_2__ Tuplesortstate ;
struct TYPE_12__ {unsigned int* t_data; unsigned int t_len; unsigned int t_self; int /*<<< orphan*/  t_tableOid; } ;
struct TYPE_11__ {int /*<<< orphan*/  isnull1; int /*<<< orphan*/  datum1; void* tuple; } ;
struct TYPE_9__ {int /*<<< orphan*/ * ii_IndexAttrNumbers; } ;
typedef  TYPE_3__ SortTuple ;
typedef  int /*<<< orphan*/  ItemPointerData ;
typedef  unsigned int* HeapTupleHeader ;
typedef  TYPE_4__* HeapTuple ;

/* Variables and functions */
 int HEAPTUPLESIZE ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  LogicalTapeReadExact (int /*<<< orphan*/ ,int,unsigned int*,int) ; 
 int /*<<< orphan*/  heap_getattr (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  readtup_alloc (TYPE_2__*,int) ; 

__attribute__((used)) static void
readtup_cluster(Tuplesortstate *state, SortTuple *stup,
				int tapenum, unsigned int tuplen)
{
	unsigned int t_len = tuplen - sizeof(ItemPointerData) - sizeof(int);
	HeapTuple	tuple = (HeapTuple) readtup_alloc(state,
												  t_len + HEAPTUPLESIZE);

	/* Reconstruct the HeapTupleData header */
	tuple->t_data = (HeapTupleHeader) ((char *) tuple + HEAPTUPLESIZE);
	tuple->t_len = t_len;
	LogicalTapeReadExact(state->tapeset, tapenum,
						 &tuple->t_self, sizeof(ItemPointerData));
	/* We don't currently bother to reconstruct t_tableOid */
	tuple->t_tableOid = InvalidOid;
	/* Read in the tuple body */
	LogicalTapeReadExact(state->tapeset, tapenum,
						 tuple->t_data, tuple->t_len);
	if (state->randomAccess)	/* need trailing length word? */
		LogicalTapeReadExact(state->tapeset, tapenum,
							 &tuplen, sizeof(tuplen));
	stup->tuple = (void *) tuple;
	/* set up first-column key value, if it's a simple column */
	if (state->indexInfo->ii_IndexAttrNumbers[0] != 0)
		stup->datum1 = heap_getattr(tuple,
									state->indexInfo->ii_IndexAttrNumbers[0],
									state->tupDesc,
									&stup->isnull1);
}