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
typedef  void ltree ;
typedef  int /*<<< orphan*/  PGCALL2 ;
typedef  int /*<<< orphan*/  ArrayType ;

/* Variables and functions */
 scalar_t__ ARR_DATA_PTR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ARR_DIMS (int /*<<< orphan*/ *) ; 
 int ARR_NDIM (int /*<<< orphan*/ *) ; 
 int ArrayGetNItems (int,int /*<<< orphan*/ ) ; 
 scalar_t__ DatumGetBool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_ARRAY_SUBSCRIPT_ERROR ; 
 int /*<<< orphan*/  ERRCODE_NULL_VALUE_NOT_ALLOWED ; 
 int /*<<< orphan*/  ERROR ; 
 void* NEXTVAL (void*) ; 
 int /*<<< orphan*/  PointerGetDatum (void*) ; 
 scalar_t__ array_contains_nulls (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 

__attribute__((used)) static bool
array_iterator(ArrayType *la, PGCALL2 callback, void *param, ltree **found)
{
	int			num = ArrayGetNItems(ARR_NDIM(la), ARR_DIMS(la));
	ltree	   *item = (ltree *) ARR_DATA_PTR(la);

	if (ARR_NDIM(la) > 1)
		ereport(ERROR,
				(errcode(ERRCODE_ARRAY_SUBSCRIPT_ERROR),
				 errmsg("array must be one-dimensional")));
	if (array_contains_nulls(la))
		ereport(ERROR,
				(errcode(ERRCODE_NULL_VALUE_NOT_ALLOWED),
				 errmsg("array must not contain nulls")));

	if (found)
		*found = NULL;
	while (num > 0)
	{
		if (DatumGetBool(DirectFunctionCall2(callback,
											 PointerGetDatum(item), PointerGetDatum(param))))
		{

			if (found)
				*found = item;
			return true;
		}
		num--;
		item = NEXTVAL(item);
	}

	return false;
}