#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int int32 ;
typedef  int bits8 ;
struct TYPE_3__ {int /*<<< orphan*/  flinfo; } ;
typedef  TYPE_1__* FunctionCallInfo ;
typedef  int /*<<< orphan*/  ArrayType ;

/* Variables and functions */
 int* ARR_DIMS (int /*<<< orphan*/ *) ; 
 int ARR_NDIM (int /*<<< orphan*/ *) ; 
 int* ARR_NULLBITMAP (int /*<<< orphan*/ *) ; 
 int ArrayGetNItems (int,int*) ; 
 int /*<<< orphan*/  Assert (int) ; 
 int OidIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ PG_ARGISNULL (int) ; 
 int /*<<< orphan*/ * PG_GETARG_ARRAYTYPE_P (int /*<<< orphan*/ ) ; 
 int PG_NARGS () ; 
 int /*<<< orphan*/  get_base_element_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_fn_expr_argtype (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ get_fn_expr_variadic (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
count_nulls(FunctionCallInfo fcinfo,
			int32 *nargs, int32 *nulls)
{
	int32		count = 0;
	int			i;

	/* Did we get a VARIADIC array argument, or separate arguments? */
	if (get_fn_expr_variadic(fcinfo->flinfo))
	{
		ArrayType  *arr;
		int			ndims,
					nitems,
				   *dims;
		bits8	   *bitmap;

		Assert(PG_NARGS() == 1);

		/*
		 * If we get a null as VARIADIC array argument, we can't say anything
		 * useful about the number of elements, so return NULL.  This behavior
		 * is consistent with other variadic functions - see concat_internal.
		 */
		if (PG_ARGISNULL(0))
			return false;

		/*
		 * Non-null argument had better be an array.  We assume that any call
		 * context that could let get_fn_expr_variadic return true will have
		 * checked that a VARIADIC-labeled parameter actually is an array.  So
		 * it should be okay to just Assert that it's an array rather than
		 * doing a full-fledged error check.
		 */
		Assert(OidIsValid(get_base_element_type(get_fn_expr_argtype(fcinfo->flinfo, 0))));

		/* OK, safe to fetch the array value */
		arr = PG_GETARG_ARRAYTYPE_P(0);

		/* Count the array elements */
		ndims = ARR_NDIM(arr);
		dims = ARR_DIMS(arr);
		nitems = ArrayGetNItems(ndims, dims);

		/* Count those that are NULL */
		bitmap = ARR_NULLBITMAP(arr);
		if (bitmap)
		{
			int			bitmask = 1;

			for (i = 0; i < nitems; i++)
			{
				if ((*bitmap & bitmask) == 0)
					count++;

				bitmask <<= 1;
				if (bitmask == 0x100)
				{
					bitmap++;
					bitmask = 1;
				}
			}
		}

		*nargs = nitems;
		*nulls = count;
	}
	else
	{
		/* Separate arguments, so just count 'em */
		for (i = 0; i < PG_NARGS(); i++)
		{
			if (PG_ARGISNULL(i))
				count++;
		}

		*nargs = PG_NARGS();
		*nulls = count;
	}

	return true;
}