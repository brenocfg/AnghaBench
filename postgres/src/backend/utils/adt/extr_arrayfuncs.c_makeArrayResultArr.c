#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int ndims; int nbytes; int /*<<< orphan*/  mcontext; int /*<<< orphan*/  private_cxt; int /*<<< orphan*/  nitems; int /*<<< orphan*/ * nullbitmap; int /*<<< orphan*/  data; int /*<<< orphan*/  lbs; int /*<<< orphan*/  dims; int /*<<< orphan*/  element_type; } ;
struct TYPE_11__ {int ndim; int dataoffset; int /*<<< orphan*/  elemtype; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  Datum ;
typedef  TYPE_1__ ArrayType ;
typedef  TYPE_2__ ArrayBuildStateArr ;

/* Variables and functions */
 int /*<<< orphan*/  ARR_DATA_PTR (TYPE_1__*) ; 
 int /*<<< orphan*/  ARR_DIMS (TYPE_1__*) ; 
 int /*<<< orphan*/  ARR_LBOUND (TYPE_1__*) ; 
 int /*<<< orphan*/  ARR_NULLBITMAP (TYPE_1__*) ; 
 scalar_t__ ARR_OVERHEAD_NONULLS (int) ; 
 int ARR_OVERHEAD_WITHNULLS (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextDelete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PointerGetDatum (TYPE_1__*) ; 
 int /*<<< orphan*/  SET_VARSIZE (TYPE_1__*,int) ; 
 int /*<<< orphan*/  array_bitmap_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* construct_empty_array (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ palloc0 (int) ; 

Datum
makeArrayResultArr(ArrayBuildStateArr *astate,
				   MemoryContext rcontext,
				   bool release)
{
	ArrayType  *result;
	MemoryContext oldcontext;

	/* Build the final array result in rcontext */
	oldcontext = MemoryContextSwitchTo(rcontext);

	if (astate->ndims == 0)
	{
		/* No inputs, return empty array */
		result = construct_empty_array(astate->element_type);
	}
	else
	{
		int			dataoffset,
					nbytes;

		/* Compute required space */
		nbytes = astate->nbytes;
		if (astate->nullbitmap != NULL)
		{
			dataoffset = ARR_OVERHEAD_WITHNULLS(astate->ndims, astate->nitems);
			nbytes += dataoffset;
		}
		else
		{
			dataoffset = 0;
			nbytes += ARR_OVERHEAD_NONULLS(astate->ndims);
		}

		result = (ArrayType *) palloc0(nbytes);
		SET_VARSIZE(result, nbytes);
		result->ndim = astate->ndims;
		result->dataoffset = dataoffset;
		result->elemtype = astate->element_type;

		memcpy(ARR_DIMS(result), astate->dims, astate->ndims * sizeof(int));
		memcpy(ARR_LBOUND(result), astate->lbs, astate->ndims * sizeof(int));
		memcpy(ARR_DATA_PTR(result), astate->data, astate->nbytes);

		if (astate->nullbitmap != NULL)
			array_bitmap_copy(ARR_NULLBITMAP(result), 0,
							  astate->nullbitmap, 0,
							  astate->nitems);
	}

	MemoryContextSwitchTo(oldcontext);

	/* Clean up all the junk */
	if (release)
	{
		Assert(astate->private_cxt);
		MemoryContextDelete(astate->mcontext);
	}

	return PointerGetDatum(result);
}