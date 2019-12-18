#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int nelems; } ;
struct TYPE_4__ {int /*<<< orphan*/  arraystate; TYPE_2__* scalarstate; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  Datum ;
typedef  TYPE_1__ ArrayBuildStateAny ;

/* Variables and functions */
 int /*<<< orphan*/  makeArrayResultArr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  makeMdArrayResult (TYPE_2__*,int,int*,int*,int /*<<< orphan*/ ,int) ; 

Datum
makeArrayResultAny(ArrayBuildStateAny *astate,
				   MemoryContext rcontext, bool release)
{
	Datum		result;

	if (astate->scalarstate)
	{
		/* Must use makeMdArrayResult to support "release" parameter */
		int			ndims;
		int			dims[1];
		int			lbs[1];

		/* If no elements were presented, we want to create an empty array */
		ndims = (astate->scalarstate->nelems > 0) ? 1 : 0;
		dims[0] = astate->scalarstate->nelems;
		lbs[0] = 1;

		result = makeMdArrayResult(astate->scalarstate, ndims, dims, lbs,
								   rcontext, release);
	}
	else
	{
		result = makeArrayResultArr(astate->arraystate,
									rcontext, release);
	}
	return result;
}