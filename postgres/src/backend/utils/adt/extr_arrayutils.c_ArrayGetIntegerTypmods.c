#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  int32 ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  ArrayType ;

/* Variables and functions */
 scalar_t__ ARR_ELEMTYPE (int /*<<< orphan*/ *) ; 
 int ARR_NDIM (int /*<<< orphan*/ *) ; 
 scalar_t__ CSTRINGOID ; 
 int /*<<< orphan*/  DatumGetCString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_ARRAY_ELEMENT_ERROR ; 
 int /*<<< orphan*/  ERRCODE_ARRAY_SUBSCRIPT_ERROR ; 
 int /*<<< orphan*/  ERRCODE_NULL_VALUE_NOT_ALLOWED ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ array_contains_nulls (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  deconstruct_array (int /*<<< orphan*/ *,scalar_t__,int,int,char,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pg_strtoint32 (int /*<<< orphan*/ ) ; 

int32 *
ArrayGetIntegerTypmods(ArrayType *arr, int *n)
{
	int32	   *result;
	Datum	   *elem_values;
	int			i;

	if (ARR_ELEMTYPE(arr) != CSTRINGOID)
		ereport(ERROR,
				(errcode(ERRCODE_ARRAY_ELEMENT_ERROR),
				 errmsg("typmod array must be type cstring[]")));

	if (ARR_NDIM(arr) != 1)
		ereport(ERROR,
				(errcode(ERRCODE_ARRAY_SUBSCRIPT_ERROR),
				 errmsg("typmod array must be one-dimensional")));

	if (array_contains_nulls(arr))
		ereport(ERROR,
				(errcode(ERRCODE_NULL_VALUE_NOT_ALLOWED),
				 errmsg("typmod array must not contain nulls")));

	/* hardwired knowledge about cstring's representation details here */
	deconstruct_array(arr, CSTRINGOID,
					  -2, false, 'c',
					  &elem_values, NULL, n);

	result = (int32 *) palloc(*n * sizeof(int32));

	for (i = 0; i < *n; i++)
		result[i] = pg_strtoint32(DatumGetCString(elem_values[i]));

	pfree(elem_values);

	return result;
}