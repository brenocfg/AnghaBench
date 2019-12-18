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
struct TYPE_7__ {int nColumns; int /*<<< orphan*/  sizeOfBloomTuple; } ;
struct TYPE_6__ {int /*<<< orphan*/  sign; int /*<<< orphan*/  heapPtr; } ;
typedef  int /*<<< orphan*/ * ItemPointer ;
typedef  int /*<<< orphan*/  Datum ;
typedef  TYPE_1__ BloomTuple ;
typedef  TYPE_2__ BloomState ;

/* Variables and functions */
 scalar_t__ palloc0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signValue (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

BloomTuple *
BloomFormTuple(BloomState *state, ItemPointer iptr, Datum *values, bool *isnull)
{
	int			i;
	BloomTuple *res = (BloomTuple *) palloc0(state->sizeOfBloomTuple);

	res->heapPtr = *iptr;

	/* Blooming each column */
	for (i = 0; i < state->nColumns; i++)
	{
		/* skip nulls */
		if (isnull[i])
			continue;

		signValue(state, res->sign, values[i], i);
	}

	return res;
}