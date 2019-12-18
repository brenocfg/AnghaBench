#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int nelems; int /*<<< orphan*/  private_cxt; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  Datum ;
typedef  TYPE_1__ ArrayBuildState ;

/* Variables and functions */
 int /*<<< orphan*/  makeMdArrayResult (TYPE_1__*,int,int*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Datum
makeArrayResult(ArrayBuildState *astate,
				MemoryContext rcontext)
{
	int			ndims;
	int			dims[1];
	int			lbs[1];

	/* If no elements were presented, we want to create an empty array */
	ndims = (astate->nelems > 0) ? 1 : 0;
	dims[0] = astate->nelems;
	lbs[0] = 1;

	return makeMdArrayResult(astate, ndims, dims, lbs, rcontext,
							 astate->private_cxt);
}