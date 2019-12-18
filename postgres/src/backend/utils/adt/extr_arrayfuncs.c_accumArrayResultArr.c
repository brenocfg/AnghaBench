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
typedef  char bits8 ;
struct TYPE_5__ {scalar_t__ array_type; int ndims; char* dims; int* lbs; int abytes; char* data; int nbytes; char* nullbitmap; int nitems; int aitems; int /*<<< orphan*/  mcontext; } ;
typedef  scalar_t__ Pointer ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  ArrayType ;
typedef  TYPE_1__ ArrayBuildStateArr ;

/* Variables and functions */
 int ARR_DATA_OFFSET (int /*<<< orphan*/ *) ; 
 char* ARR_DATA_PTR (int /*<<< orphan*/ *) ; 
 int* ARR_DIMS (int /*<<< orphan*/ *) ; 
 scalar_t__ ARR_HASNULL (int /*<<< orphan*/ *) ; 
 int* ARR_LBOUND (int /*<<< orphan*/ *) ; 
 int ARR_NDIM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ARR_NULLBITMAP (int /*<<< orphan*/ *) ; 
 int ARR_SIZE (int /*<<< orphan*/ *) ; 
 int ArrayGetNItems (int,int*) ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/ * DatumGetArrayTypeP (int /*<<< orphan*/ ) ; 
 scalar_t__ DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_ARRAY_SUBSCRIPT_ERROR ; 
 int /*<<< orphan*/  ERRCODE_NULL_VALUE_NOT_ALLOWED ; 
 int /*<<< orphan*/  ERRCODE_PROGRAM_LIMIT_EXCEEDED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  InvalidOid ; 
 int MAXDIM ; 
 void* Max (int,int) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  array_bitmap_copy (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 TYPE_1__* initArrayResultArr (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (char*,...) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 
 scalar_t__ repalloc (char*,int) ; 

ArrayBuildStateArr *
accumArrayResultArr(ArrayBuildStateArr *astate,
					Datum dvalue, bool disnull,
					Oid array_type,
					MemoryContext rcontext)
{
	ArrayType  *arg;
	MemoryContext oldcontext;
	int		   *dims,
			   *lbs,
				ndims,
				nitems,
				ndatabytes;
	char	   *data;
	int			i;

	/*
	 * We disallow accumulating null subarrays.  Another plausible definition
	 * is to ignore them, but callers that want that can just skip calling
	 * this function.
	 */
	if (disnull)
		ereport(ERROR,
				(errcode(ERRCODE_NULL_VALUE_NOT_ALLOWED),
				 errmsg("cannot accumulate null arrays")));

	/* Detoast input array in caller's context */
	arg = DatumGetArrayTypeP(dvalue);

	if (astate == NULL)
		astate = initArrayResultArr(array_type, InvalidOid, rcontext, true);
	else
		Assert(astate->array_type == array_type);

	oldcontext = MemoryContextSwitchTo(astate->mcontext);

	/* Collect this input's dimensions */
	ndims = ARR_NDIM(arg);
	dims = ARR_DIMS(arg);
	lbs = ARR_LBOUND(arg);
	data = ARR_DATA_PTR(arg);
	nitems = ArrayGetNItems(ndims, dims);
	ndatabytes = ARR_SIZE(arg) - ARR_DATA_OFFSET(arg);

	if (astate->ndims == 0)
	{
		/* First input; check/save the dimensionality info */

		/* Should we allow empty inputs and just produce an empty output? */
		if (ndims == 0)
			ereport(ERROR,
					(errcode(ERRCODE_ARRAY_SUBSCRIPT_ERROR),
					 errmsg("cannot accumulate empty arrays")));
		if (ndims + 1 > MAXDIM)
			ereport(ERROR,
					(errcode(ERRCODE_PROGRAM_LIMIT_EXCEEDED),
					 errmsg("number of array dimensions (%d) exceeds the maximum allowed (%d)",
							ndims + 1, MAXDIM)));

		/*
		 * The output array will have n+1 dimensions, with the ones after the
		 * first matching the input's dimensions.
		 */
		astate->ndims = ndims + 1;
		astate->dims[0] = 0;
		memcpy(&astate->dims[1], dims, ndims * sizeof(int));
		astate->lbs[0] = 1;
		memcpy(&astate->lbs[1], lbs, ndims * sizeof(int));

		/* Allocate at least enough data space for this item */
		astate->abytes = 1024;
		while (astate->abytes <= ndatabytes)
			astate->abytes *= 2;
		astate->data = (char *) palloc(astate->abytes);
	}
	else
	{
		/* Second or later input: must match first input's dimensionality */
		if (astate->ndims != ndims + 1)
			ereport(ERROR,
					(errcode(ERRCODE_ARRAY_SUBSCRIPT_ERROR),
					 errmsg("cannot accumulate arrays of different dimensionality")));
		for (i = 0; i < ndims; i++)
		{
			if (astate->dims[i + 1] != dims[i] || astate->lbs[i + 1] != lbs[i])
				ereport(ERROR,
						(errcode(ERRCODE_ARRAY_SUBSCRIPT_ERROR),
						 errmsg("cannot accumulate arrays of different dimensionality")));
		}

		/* Enlarge data space if needed */
		if (astate->nbytes + ndatabytes > astate->abytes)
		{
			astate->abytes = Max(astate->abytes * 2,
								 astate->nbytes + ndatabytes);
			astate->data = (char *) repalloc(astate->data, astate->abytes);
		}
	}

	/*
	 * Copy the data portion of the sub-array.  Note we assume that the
	 * advertised data length of the sub-array is properly aligned.  We do not
	 * have to worry about detoasting elements since whatever's in the
	 * sub-array should be OK already.
	 */
	memcpy(astate->data + astate->nbytes, data, ndatabytes);
	astate->nbytes += ndatabytes;

	/* Deal with null bitmap if needed */
	if (astate->nullbitmap || ARR_HASNULL(arg))
	{
		int			newnitems = astate->nitems + nitems;

		if (astate->nullbitmap == NULL)
		{
			/*
			 * First input with nulls; we must retrospectively handle any
			 * previous inputs by marking all their items non-null.
			 */
			astate->aitems = 256;
			while (astate->aitems <= newnitems)
				astate->aitems *= 2;
			astate->nullbitmap = (bits8 *) palloc((astate->aitems + 7) / 8);
			array_bitmap_copy(astate->nullbitmap, 0,
							  NULL, 0,
							  astate->nitems);
		}
		else if (newnitems > astate->aitems)
		{
			astate->aitems = Max(astate->aitems * 2, newnitems);
			astate->nullbitmap = (bits8 *)
				repalloc(astate->nullbitmap, (astate->aitems + 7) / 8);
		}
		array_bitmap_copy(astate->nullbitmap, astate->nitems,
						  ARR_NULLBITMAP(arg), 0,
						  nitems);
	}

	astate->nitems += nitems;
	astate->dims[0] += 1;

	MemoryContextSwitchTo(oldcontext);

	/* Release detoasted copy if any */
	if ((Pointer) arg != DatumGetPointer(dvalue))
		pfree(arg);

	return astate;
}