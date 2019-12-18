#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  float4 ;
struct TYPE_6__ {int /*<<< orphan*/  typalign; int /*<<< orphan*/  typbyval; int /*<<< orphan*/  typlen; int /*<<< orphan*/  type_id; } ;
typedef  TYPE_1__ TypeCacheEntry ;
typedef  double Selectivity ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int Datum ;
typedef  int /*<<< orphan*/  ArrayType ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  OID_ARRAY_CONTAINED_OP ; 
 int /*<<< orphan*/  OID_ARRAY_CONTAINS_OP ; 
 int /*<<< orphan*/  OID_ARRAY_OVERLAP_OP ; 
 int /*<<< orphan*/  deconstruct_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int**,int**,int*) ; 
 int /*<<< orphan*/  element_compare ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 double mcelem_array_contain_overlap_selec (int*,int,int /*<<< orphan*/ *,int,int*,int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 double mcelem_array_contained_selec (int*,int,int /*<<< orphan*/ *,int,int*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  pfree (int*) ; 
 int /*<<< orphan*/  qsort_arg (int*,int,int,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static Selectivity
mcelem_array_selec(ArrayType *array, TypeCacheEntry *typentry,
				   Datum *mcelem, int nmcelem,
				   float4 *numbers, int nnumbers,
				   float4 *hist, int nhist,
				   Oid operator)
{
	Selectivity selec;
	int			num_elems;
	Datum	   *elem_values;
	bool	   *elem_nulls;
	bool		null_present;
	int			nonnull_nitems;
	int			i;

	/*
	 * Prepare constant array data for sorting.  Sorting lets us find unique
	 * elements and efficiently merge with the MCELEM array.
	 */
	deconstruct_array(array,
					  typentry->type_id,
					  typentry->typlen,
					  typentry->typbyval,
					  typentry->typalign,
					  &elem_values, &elem_nulls, &num_elems);

	/* Collapse out any null elements */
	nonnull_nitems = 0;
	null_present = false;
	for (i = 0; i < num_elems; i++)
	{
		if (elem_nulls[i])
			null_present = true;
		else
			elem_values[nonnull_nitems++] = elem_values[i];
	}

	/*
	 * Query "column @> '{anything, null}'" matches nothing.  For the other
	 * two operators, presence of a null in the constant can be ignored.
	 */
	if (null_present && operator == OID_ARRAY_CONTAINS_OP)
	{
		pfree(elem_values);
		pfree(elem_nulls);
		return (Selectivity) 0.0;
	}

	/* Sort extracted elements using their default comparison function. */
	qsort_arg(elem_values, nonnull_nitems, sizeof(Datum),
			  element_compare, typentry);

	/* Separate cases according to operator */
	if (operator == OID_ARRAY_CONTAINS_OP || operator == OID_ARRAY_OVERLAP_OP)
		selec = mcelem_array_contain_overlap_selec(mcelem, nmcelem,
												   numbers, nnumbers,
												   elem_values, nonnull_nitems,
												   operator, typentry);
	else if (operator == OID_ARRAY_CONTAINED_OP)
		selec = mcelem_array_contained_selec(mcelem, nmcelem,
											 numbers, nnumbers,
											 elem_values, nonnull_nitems,
											 hist, nhist,
											 operator, typentry);
	else
	{
		elog(ERROR, "arraycontsel called for unrecognized operator %u",
			 operator);
		selec = 0.0;			/* keep compiler quiet */
	}

	pfree(elem_values);
	pfree(elem_nulls);
	return selec;
}