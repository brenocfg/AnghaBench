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
struct TYPE_7__ {unsigned int size; int /*<<< orphan*/  heapPtr; int /*<<< orphan*/  nextOffset; } ;
struct TYPE_6__ {int /*<<< orphan*/  attLeafType; } ;
typedef  TYPE_1__ SpGistState ;
typedef  TYPE_2__* SpGistLeafTuple ;
typedef  int /*<<< orphan*/ * ItemPointer ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidOffsetNumber ; 
 unsigned int SGDTSIZE ; 
 int /*<<< orphan*/  SGLTDATAPTR (TYPE_2__*) ; 
 unsigned int SGLTHDRSZ ; 
 scalar_t__ SpGistGetTypeSize (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpyDatum (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ palloc0 (unsigned int) ; 

SpGistLeafTuple
spgFormLeafTuple(SpGistState *state, ItemPointer heapPtr,
				 Datum datum, bool isnull)
{
	SpGistLeafTuple tup;
	unsigned int size;

	/* compute space needed (note result is already maxaligned) */
	size = SGLTHDRSZ;
	if (!isnull)
		size += SpGistGetTypeSize(&state->attLeafType, datum);

	/*
	 * Ensure that we can replace the tuple with a dead tuple later.  This
	 * test is unnecessary when !isnull, but let's be safe.
	 */
	if (size < SGDTSIZE)
		size = SGDTSIZE;

	/* OK, form the tuple */
	tup = (SpGistLeafTuple) palloc0(size);

	tup->size = size;
	tup->nextOffset = InvalidOffsetNumber;
	tup->heapPtr = *heapPtr;
	if (!isnull)
		memcpyDatum(SGLTDATAPTR(tup), &state->attLeafType, datum);

	return tup;
}